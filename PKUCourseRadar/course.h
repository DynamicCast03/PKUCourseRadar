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
    bool liked=false;
    bool operator==(const Course& other) const;
};


inline bool Course::operator==(const Course& other) const
{
    return (ct == other.ct) &&
           (name == other.name) &&
           (building == other.building) &&
           (room == other.room) &&
           (teacher == other.teacher) &&
           (tags == other.tags);
}

inline uint qHash(const Course& key, uint seed = 0)
{
    uint hash = seed;
    hash = qHash(key.ct, hash);
    hash = qHash(key.name, hash);
    hash = qHash(key.building, hash);
    hash = qHash(key.room, hash);
    hash = qHash(key.teacher, hash);
    for (const QString& tag : key.tags) {
        hash = qHash(tag, hash);
    }
    return hash;
}

#endif // COURSE_H
