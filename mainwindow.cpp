#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "postwidget.h"
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include <QSettings>
#include <QCoreApplication>
#include <QFileDialog>
#include <QDateTime>
#include <QThread>
#include <utility> 

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_scheduler(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Facebook Bulk Scheduler");

    loadSettings();

    ui->startDateTimeEdit->setDateTime(QDateTime::currentDateTime().addSecs(7200));

    connect(this, &MainWindow::updateStatus, this, &MainWindow::on_updateStatus, Qt::QueuedConnection);
    connect(this, &MainWindow::allJobsFinished, this, &MainWindow::on_allJobsFinished, Qt::QueuedConnection);

    on_addPostButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_scheduler;
}

void MainWindow::on_fetchPagesButton_clicked()
{
    QString token = ui->accessTokenLineEdit->text().trimmed();
    if (token.isEmpty()) {
        QMessageBox::warning(this, "Missing Token", "Please paste your Access Token first.");
        return;
    }

    statusBar()->showMessage("Fetching pages from Facebook...");
    QApplication::processEvents(); 

    std::vector<FacebookPage> pages = FacebookScheduler::fetchManagedPages(token.toStdString());

    if (pages.empty()) {
        QMessageBox::warning(this, "Error", "Could not fetch any pages. Check your token or network connection.");
        statusBar()->showMessage("Failed to fetch pages.");
        return;
    }

    for (const auto& page : pages) {
        QStringList dataList;
        dataList << QString::fromStdString(page.id) << QString::fromStdString(page.token);
        QString pageName = QString::fromStdString(page.name);
        
        bool exists = false;
        for (int i = 0; i < ui->pageComboBox->count(); ++i) {
            QStringList existingData = ui->pageComboBox->itemData(i).toStringList();
            if (existingData.size() == 2 && existingData[0] == QString::fromStdString(page.id)) {
                exists = true;
                ui->pageComboBox->setItemText(i, pageName);
                ui->pageComboBox->setItemData(i, dataList); 
                break;
            }
        }
        
        if (!exists) {
            ui->pageComboBox->addItem(pageName, dataList);
        }
    }

    saveSettings(); 
    statusBar()->showMessage("Pages loaded and saved successfully.");
}

void MainWindow::on_pageComboBox_currentIndexChanged(int index) {
    if (index >= 0) {
        QStringList dataList = ui->pageComboBox->itemData(index).toStringList();
        if (dataList.size() == 2) {
            ui->pageIdLineEdit->blockSignals(true);
            ui->accessTokenLineEdit->blockSignals(true);
            
            ui->pageIdLineEdit->setText(dataList[0]);
            ui->accessTokenLineEdit->setText(dataList[1]);
            
            ui->pageIdLineEdit->blockSignals(false);
            ui->accessTokenLineEdit->blockSignals(false);
        }
    }
    initializeScheduler(); 
}

void MainWindow::on_pageIdLineEdit_textChanged(const QString &arg1) {
    Q_UNUSED(arg1);
    initializeScheduler();
}

void MainWindow::on_accessTokenLineEdit_textChanged(const QString &arg1) {
    Q_UNUSED(arg1);
    initializeScheduler();
}

void MainWindow::updateAllPostTimes()
{
    int strategyIndex = ui->strategyComboBox->currentIndex();
    if (strategyIndex == 0) return; 

    QDateTime currentScheduleTime = ui->startDateTimeEdit->dateTime();
    
    for (int i = 0; i < ui->postsLayout->count(); ++i) {
        if (auto* widget = ui->postsLayout->itemAt(i)->widget()) {
            if (auto* postWidget = qobject_cast<PostWidget*>(widget)) {
                
                postWidget->setScheduleTime(currentScheduleTime);
                
                if (strategyIndex == 1) { 
                    currentScheduleTime = currentScheduleTime.addSecs(3600);
                } else if (strategyIndex == 2) { 
                    currentScheduleTime = currentScheduleTime.addDays(1);
                } else if (strategyIndex == 3) { 
                    currentScheduleTime = currentScheduleTime.addSecs(12 * 3600);
                }
            }
        }
    }
}

void MainWindow::on_addPostButton_clicked()
{
    PostWidget* newPost = new PostWidget(this);
    ui->postsLayout->addWidget(newPost);
    connect(newPost, &PostWidget::removeClicked, this, &MainWindow::on_removePostWidget);
    updateAllPostTimes(); 
}

void MainWindow::on_bulkAddButton_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(
        this, 
        "Select Multiple Media Files", 
        QDir::homePath(), 
        "All Supported Media (*.jpg *.png *.mp4 *.mov);;Images (*.jpg *.png);;Videos (*.mp4 *.mov)"
    );

    if (files.isEmpty()) return;

    QStringList finalSafeFiles;
    QStringList folderErrors;

    for (const QString& file : std::as_const(files)) {
        QFileInfo info(file);
        QString dirPath = info.absolutePath();
        QString baseName = info.completeBaseName();
        QString suffix = info.suffix();

        bool dirSafe = true;
        for (QChar c : dirPath) {
            if (c.unicode() > 127) { dirSafe = false; break; }
        }

        if (!dirSafe) {
            folderErrors.append(info.fileName() + " (Folder contains special characters)");
            continue;
        }

        QString cleanBase = "";
        bool needsRename = false;
        for (QChar c : baseName) {
            if (c.unicode() <= 127) {
                cleanBase += c;
            } else {
                needsRename = true; 
            }
        }

        QString finalPath = file;
        if (needsRename) {
            if (cleanBase.trimmed().isEmpty()) cleanBase = "auto_renamed_media";
            QString newPath = dirPath + "/" + cleanBase + "." + suffix;
            
            if (QFile::rename(file, newPath)) {
                finalPath = newPath; 
            } else {
                folderErrors.append(info.fileName() + " (Failed to auto-rename, might be open in another app)");
                continue;
            }
        }
        finalSafeFiles.append(finalPath);
    }

    if (!folderErrors.isEmpty()) {
        QMessageBox::warning(this, "Some files skipped",
            "The following files could not be auto-fixed because their FOLDER contains special characters, or they are locked by another app:\n\n" +
            folderErrors.join("\n") +
            "\n\nMove them to a standard folder (like C:/videos) and try again.");
    }

    if (finalSafeFiles.isEmpty()) return;

    QList<PostWidget*> emptyWidgets;
    for (int i = 0; i < ui->postsLayout->count(); ++i) {
        if (auto* widget = ui->postsLayout->itemAt(i)->widget()) {
            if (auto* postWidget = qobject_cast<PostWidget*>(widget)) {
                if (postWidget->getPostJob().filePath.isEmpty()) {
                    emptyWidgets.append(postWidget);
                }
            }
        }
    }

    for (PostWidget* emptyWidget : emptyWidgets) {
        on_removePostWidget(emptyWidget);
    }

    // --- GPU CRASH FIX: Staggered Loading Loop ---
    int staggerDelay = 0;
    
    for (const QString& file : std::as_const(finalSafeFiles)) {
        PostWidget* newPost = new PostWidget(this);
        
        newPost->setFilePath(file, staggerDelay);
        ui->postsLayout->addWidget(newPost);
        connect(newPost, &PostWidget::removeClicked, this, &MainWindow::on_removePostWidget);
        
        staggerDelay += 300; 
    }
    // ---------------------------------------------
    
    updateAllPostTimes();
}

void MainWindow::on_scheduleAllButton_clicked()
{
    if (!m_scheduler) {
        QMessageBox::critical(this, "Error", "Scheduler not initialized. Make sure you entered an Access Token and Page ID.");
        return;
    }

    QList<PostJob> allJobs;
    for (int i = 0; i < ui->postsLayout->count(); ++i)
    {
        if (auto* widget = ui->postsLayout->itemAt(i)->widget()) {
            if (auto* postWidget = qobject_cast<PostWidget*>(widget))
            {
                PostJob job = postWidget->getPostJob();
                if (!job.filePath.isEmpty()) {
                    allJobs.append(job);
                }
            }
        }
    }

    if (allJobs.isEmpty()) {
        QMessageBox::information(this, "Empty", "No posts with valid files found.");
        return;
    }

    ui->scheduleAllButton->setEnabled(false);
    ui->addPostButton->setEnabled(false);
    ui->bulkAddButton->setEnabled(false);

    (void)QtConcurrent::run([this, allJobs]() {
        runBulkSchedule(allJobs);
    });
}

void MainWindow::runBulkSchedule(const QList<PostJob>& jobs)
{
    int count = 1;
    for (const PostJob& job : std::as_const(jobs))
    {
        emit updateStatus(QString("Uploading %1 of %2").arg(count).arg(jobs.count()));

        ApiResponse response;
        if (job.type == PostJob::PostType::Video) {
            response = m_scheduler->scheduleVideo(job.filePath.toStdString(),
                                                  job.description.toStdString(),
                                                  job.scheduleTime.toSecsSinceEpoch());
        } else {
            response = m_scheduler->schedulePhoto(job.filePath.toStdString(),
                                                  job.description.toStdString(),
                                                  job.scheduleTime.toSecsSinceEpoch());
        }

        if (!response.success) {
            emit updateStatus("Error on item " + QString::number(count) + ": " + QString::fromStdString(response.message));
        } else {
            emit updateStatus("Success on item " + QString::number(count));
        }

        if (count < jobs.count()) {
            emit updateStatus(QString("Cooldown: Waiting 3 seconds..."));
            QThread::sleep(3); 
        }

        count++;
    }
    emit allJobsFinished();
}

void MainWindow::on_removePostWidget(PostWidget* widget)
{
    ui->postsLayout->removeWidget(widget);
    widget->deleteLater();
    updateAllPostTimes();
}

void MainWindow::on_saveSettingsButton_clicked()
{
    saveSettings();
    statusBar()->showMessage("Settings saved successfully.");
}

void MainWindow::on_updateStatus(const QString& message)
{
    statusBar()->showMessage(message);
    QString timestamp = QDateTime::currentDateTime().toString("[hh:mm:ss] ");
    ui->logTextEdit->append(timestamp + message);
}

void MainWindow::on_allJobsFinished()
{
    ui->scheduleAllButton->setEnabled(true);
    ui->addPostButton->setEnabled(true);
    ui->bulkAddButton->setEnabled(true);
    QMessageBox::information(this, "Finished", "All jobs processed.");
}

void MainWindow::on_strategyComboBox_currentIndexChanged(int index) {
    Q_UNUSED(index);
    updateAllPostTimes();
}

void MainWindow::on_startDateTimeEdit_dateTimeChanged(const QDateTime &dateTime) {
    Q_UNUSED(dateTime);
    updateAllPostTimes();
}

void MainWindow::loadSettings()
{
    QSettings settings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);

    ui->pageComboBox->clear();

    int size = settings.beginReadArray("SavedPages");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        QString name = settings.value("Name").toString();
        QString pageId = settings.value("PageID").toString();
        QString token = settings.value("Token").toString();

        QStringList dataList;
        dataList << pageId << token;
        ui->pageComboBox->addItem(name, dataList);
    }
    settings.endArray();

    if (size == 0) {
        QString oldId = settings.value("Credentials/PageID").toString();
        QString oldToken = settings.value("Credentials/AccessToken").toString();
        if (!oldId.isEmpty() && !oldToken.isEmpty()) {
            QStringList dataList;
            dataList << oldId << oldToken;
            ui->pageComboBox->addItem("Saved Page: " + oldId, dataList);
        }
    }

    QString lastActiveId = settings.value("LastActivePageID").toString();
    bool found = false;
    for (int i = 0; i < ui->pageComboBox->count(); ++i) {
        QStringList data = ui->pageComboBox->itemData(i).toStringList();
        if (data.size() > 0 && data[0] == lastActiveId) {
            ui->pageComboBox->setCurrentIndex(i);
            ui->pageIdLineEdit->setText(data[0]);
            ui->accessTokenLineEdit->setText(data[1]);
            found = true;
            break;
        }
    }

    if (!found && ui->pageComboBox->count() > 0) {
        ui->pageComboBox->setCurrentIndex(0);
        QStringList data = ui->pageComboBox->itemData(0).toStringList();
        ui->pageIdLineEdit->setText(data[0]);
        ui->accessTokenLineEdit->setText(data[1]);
    }

    initializeScheduler();
}

void MainWindow::saveSettings()
{
    QSettings settings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);

    QString currentToken = ui->accessTokenLineEdit->text().trimmed();
    QString currentId = ui->pageIdLineEdit->text().trimmed();
    
    if (!currentId.isEmpty() && !currentToken.isEmpty()) {
        bool exists = false;
        for (int i = 0; i < ui->pageComboBox->count(); ++i) {
            QStringList data = ui->pageComboBox->itemData(i).toStringList();
            if (data.size() == 2 && data[0] == currentId) {
                exists = true;
                data[1] = currentToken;
                ui->pageComboBox->setItemData(i, data);
                break;
            }
        }
        
        if (!exists) {
            QStringList dataList;
            dataList << currentId << currentToken;
            ui->pageComboBox->addItem("Manual Page: " + currentId, dataList);
            ui->pageComboBox->setCurrentIndex(ui->pageComboBox->count() - 1);
        }
    }

    settings.beginWriteArray("SavedPages");
    for (int i = 0; i < ui->pageComboBox->count(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("Name", ui->pageComboBox->itemText(i));
        QStringList data = ui->pageComboBox->itemData(i).toStringList();
        if (data.size() == 2) {
            settings.setValue("PageID", data[0]);
            settings.setValue("Token", data[1]);
        }
    }
    settings.endArray();

    settings.setValue("LastActivePageID", currentId);
    
    statusBar()->showMessage("Account list saved successfully.");
}

void MainWindow::initializeScheduler()
{
    delete m_scheduler;
    m_scheduler = nullptr;

    QString pageId = ui->pageIdLineEdit->text().trimmed();
    QString token = ui->accessTokenLineEdit->text().trimmed();

    QString finalToken = token;
    int currentIndex = ui->pageComboBox->currentIndex();
    if (currentIndex >= 0) {
        QStringList dataList = ui->pageComboBox->itemData(currentIndex).toStringList();
        if (dataList.size() == 2 && dataList[0] == pageId) {
            finalToken = dataList[1];
        }
    }

    if (!pageId.isEmpty() && !finalToken.isEmpty()) {
        m_scheduler = new FacebookScheduler(pageId.toStdString(), finalToken.toStdString());
    }
}