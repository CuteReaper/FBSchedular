#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "FacebookScheduler.h"
#include "postjob.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class PostWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void updateStatus(const QString& message);
    void allJobsFinished();

private slots:
    void on_addPostButton_clicked();
    void on_bulkAddButton_clicked();
    void on_scheduleAllButton_clicked();
    void on_saveSettingsButton_clicked();
    void on_removePostWidget(PostWidget* widget);
    void on_updateStatus(const QString& message);
    void on_allJobsFinished();
    void on_strategyComboBox_currentIndexChanged(int index);
    void on_startDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    // Page Fetching & Manual Entry
    void on_fetchPagesButton_clicked();
    void on_pageComboBox_currentIndexChanged(int index);
    void on_pageIdLineEdit_textChanged(const QString &arg1);     // NEW
    void on_accessTokenLineEdit_textChanged(const QString &arg1); // NEW

private:
    void loadSettings();
    void saveSettings();
    void initializeScheduler();
    void runBulkSchedule(const QList<PostJob>& jobs);
    void updateAllPostTimes();

    Ui::MainWindow *ui;
    FacebookScheduler* m_scheduler;
};

#endif // MAINWINDOW_H