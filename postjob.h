#ifndef POSTJOB_H
#define POSTJOB_H

#include <QString>
#include <QDateTime>

struct PostJob {
    enum class PostType { Photo, Video };
    PostType type = PostType::Photo;
    QString filePath;
    QString description;
    QDateTime scheduleTime;
};

#endif // POSTJOB_H