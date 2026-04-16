#include "postwidget.h"
#include "ui_postwidget.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QUrl>
#include <QPixmap>
#include <QVideoFrame>
#include <QMediaPlayer>
#include <QVideoSink>
#include <QMessageBox>

PostWidget::PostWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::PostWidget),
    m_mediaPlayer(new QMediaPlayer(this)), m_videoSink(new QVideoSink(this))
{
    ui->setupUi(this);
    ui->dateTimePicker->setDateTime(QDateTime::currentDateTime().addSecs(7200));
    m_mediaPlayer->setVideoSink(m_videoSink);

    connect(m_videoSink, &QVideoSink::videoFrameChanged, this, &PostWidget::processFrame);
    connect(ui->photoRadioButton, &QRadioButton::toggled, this, &PostWidget::on_mediaType_toggled);
}

PostWidget::~PostWidget() {
    delete ui;
}

PostJob PostWidget::getPostJob() const {
    if (m_mediaPlayer) {
        m_mediaPlayer->stop();
        m_mediaPlayer->setSource(QUrl());
    }

    PostJob job;
    job.type = ui->photoRadioButton->isChecked() ? PostJob::PostType::Photo : PostJob::PostType::Video;
    job.filePath = ui->filePathLineEdit->text();
    job.description = ui->descriptionTextEdit->toPlainText();
    job.scheduleTime = ui->dateTimePicker->dateTime();
    return job;
}

void PostWidget::setScheduleTime(const QDateTime& time) {
    ui->dateTimePicker->setDateTime(time);
}

void PostWidget::on_browseButton_clicked() {
    QString filter = ui->photoRadioButton->isChecked() ? "Images (*.jpg *.png)" : "Videos (*.mp4 *.mov)";
    QString path = QFileDialog::getOpenFileName(this, "Select File", QDir::homePath(), filter);

    if (!path.isEmpty()) {
        QFileInfo info(path);
        QString dirPath = info.absolutePath();
        QString baseName = info.completeBaseName();
        QString suffix = info.suffix();

        // 1. Check if the folder has bad characters (we cannot safely rename user folders)
        for (QChar c : dirPath) {
            if (c.unicode() > 127) {
                QMessageBox::warning(this, "Invalid Folder", "The folder path contains special characters. Please move the file to a standard folder and try again.");
                return;
            }
        }

        // 2. Automatically remove bad characters from the file name
        QString cleanBase = "";
        bool needsRename = false;
        for (QChar c : baseName) {
            if (c.unicode() <= 127) {
                cleanBase += c;
            } else {
                needsRename = true; // Drop the character
            }
        }

        QString finalPath = path;

        // 3. Rename the actual file on the hard drive
        if (needsRename) {
            if (cleanBase.trimmed().isEmpty()) cleanBase = "auto_renamed_media";
            QString newPath = dirPath + "/" + cleanBase + "." + suffix;

            if (QFile::rename(path, newPath)) {
                finalPath = newPath; // Successfully stripped characters!
            } else {
                QMessageBox::warning(this, "Rename Failed", "Could not automatically remove the character. The file might be open in another program.");
                return;
            }
        }

        setFilePath(finalPath);
    }
}

void PostWidget::setFilePath(const QString& path) {
    QString lowerPath = path.toLower();

    if (lowerPath.endsWith(".mp4") || lowerPath.endsWith(".mov")) {
        ui->videoRadioButton->setChecked(true);
    } else {
        ui->photoRadioButton->setChecked(true);
    }

    ui->filePathLineEdit->setText(path);

    QFileInfo fileInfo(path);
    ui->descriptionTextEdit->setText(fileInfo.completeBaseName());

    if (ui->videoRadioButton->isChecked()) {
        m_mediaPlayer->setSource(QUrl::fromLocalFile(path));
        m_mediaPlayer->play();
    } else {
        QPixmap pixmap(path);
        ui->previewLabel->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio));
    }
}

void PostWidget::processFrame(const QVideoFrame &frame) {
    if (frame.isValid()) {
        ui->previewLabel->setPixmap(QPixmap::fromImage(frame.toImage()).scaled(150, 150, Qt::KeepAspectRatio));
        m_mediaPlayer->stop();
        m_mediaPlayer->setSource(QUrl());
    }
}

void PostWidget::on_mediaType_toggled() {
    ui->filePathLineEdit->clear();
    ui->previewLabel->clear();
    m_mediaPlayer->stop();
}

void PostWidget::on_removeButton_clicked() { emit removeClicked(this); }
void PostWidget::handleMediaPlayerError() {}
void PostWidget::setFileData(const QString& filePath, const QString& fileNameOnly) {}