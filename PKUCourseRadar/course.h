#ifndef COURSE_H
#define COURSE_H

#include "coursetime.h"
#include "utils.h"

class Course : public QObject {
    Q_OBJECT
public:
    Course();
    Course(const Course& c);
    Course& operator=(const Course& c);
    double rating();
    CourseTime ct;
    QUuid id;
    QString name, building, room, teacher;
    QSet<QString> tags;
    QVector<QUuid> comments;
    QString note;
    QString description();
    QString tagsString();
    bool include(int day, int session) const;
    bool marked = false;
    bool operator==(const Course& other) const;
};

inline bool Course::operator==(const Course& other) const
{
    return id == other.id;
}

inline uint qHash(const Course& key, uint seed = 0)
{
    uint hash = seed;
    hash = qHash(key.id, hash);
    return hash;
}

#endif // COURSE_H
