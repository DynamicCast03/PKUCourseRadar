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
    bool operator==(const CourseTime& other) const;
};


inline bool CourseTime::operator==(const CourseTime& other) const
{
    return table == other.table;
}

inline uint qHash(const CourseTime& key, uint seed = 0)
{
    uint hash = seed;
    for (const auto& day : key.table) {
        for (int session : day) {
            hash = qHash(session, hash);
        }
    }
    return hash;
}
#endif // COURSETIME_H
