#ifndef COURSETIME_H
#define COURSETIME_H

#include "utils.h"

class CourseTime : public QObject
{
    Q_OBJECT
public:
    CourseTime();
    CourseTime(const CourseTime& ct);
    CourseTime& operator=(const CourseTime& ct);
    QVector<QVector<int>> table;
    void add(int day, int session);
    bool conflict(const CourseTime& ct);
    QString toString();
};

#endif // COURSETIME_H
