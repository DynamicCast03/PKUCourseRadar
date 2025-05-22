#ifndef COURSEMANAGER_H
#define COURSEMANAGER_H

#include "utils.h"
#include "course.h"

class CourseManager
{
public:
    CourseManager();
    QSet<Course> AllCourses;
    bool readFromFile(QFile& file);
    bool writeToFile(QFile& file);
    QSet<Course> searchByName(QString name);
    QSet<Course> searchByTags(QSet<QString> tags);
};

#endif // COURSEMANAGER_H
