#ifndef COURSE_H
#define COURSE_H

#include "utils.h"
#include "coursetime.h"

class Course : public QObject
{
    Q_OBJECT
public:
    Course();
    Course(const Course& c);
    Course& operator=(const Course& c);

    CourseTime ct;
    QString name, building, room, teacher;
    QSet<QString> tags;
    QString note;
    QString description();
    QString tagsString();
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
