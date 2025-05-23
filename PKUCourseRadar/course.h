#ifndef COURSE_H
#define COURSE_H

#include "utils.h"
#include "coursetime.h"

class Course
{
public:
    Course();
    CourseTime ct;
    QString name, building, room;
    QSet<QString> tags;

};

inline bool operator==(const Course& lhs, const Course& rhs)
{
    return lhs.name == rhs.name;
}

inline uint qHash(const Course& course, uint seed = 0)
{
    return qHash(course.name, seed);
}

#endif // COURSE_H
