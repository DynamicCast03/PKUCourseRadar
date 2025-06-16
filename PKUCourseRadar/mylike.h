#ifndef MYLIKE_H
#define MYLIKE_H

#include <QObject>
#include "course.h"
#include "utils.h"

class MarkedCourseManager : public QObject
{
    Q_OBJECT
public:
    explicit MarkedCourseManager(QObject *parent = nullptr);
    static MarkedCourseManager theMarkedManager;
    QVector<Course> all_marked_courses;

signals:
};

#endif // MYLIKE_H
