#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoSink>
#include "postjob.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PostWidget; }
QT_END_NAMESPACE

class PostWidget : public QWidget {
    Q_OBJECT

public:
    explicit PostWidget(QWidget *parent = nullptr);
    ~PostWidget();

    PostJob getPostJob() const;
    void setFileData(const QString& filePath, const QString& fileNameOnly);
    void setScheduleTime(const QDateTime& time);
    void setFilePath(const QString& path);

signals:
    void removeClicked(PostWidget* widget);

private slots:
    void on_browseButton_clicked();
    void on_mediaType_toggled();
    void on_removeButton_clicked();
    void processFrame(const QVideoFrame &frame);
    void handleMediaPlayerError();

private:
    Ui::PostWidget *ui;
    QMediaPlayer *m_mediaPlayer;
    QVideoSink *m_videoSink;
};

#endif // POSTWIDGET_H