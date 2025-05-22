#ifndef COURSETIME_H
#define COURSETIME_H

#include "utils.h"

class CourseTime
{
public:
    CourseTime();
    QVector<int> table;
    void add(int day, int session);
    bool conflict(const CourseTime& ct);
};

#endif // COURSETIME_H
