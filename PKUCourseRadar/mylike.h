#ifndef MYLIKE_H
#define MYLIKE_H

#include <QObject>
#include "course.h"
#include "utils.h"

class MyLike : public QObject
{
    Q_OBJECT
public:
    explicit MyLike(QObject *parent = nullptr);
    static MyLike the_liked;
    QVector<Course> All_Liked;

signals:
};

#endif // MYLIKE_H
