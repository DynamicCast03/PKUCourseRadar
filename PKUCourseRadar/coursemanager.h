#ifndef COURSEMANAGER_H
#define COURSEMANAGER_H

#include "utils.h"
#include "course.h"

class CourseManager : public QObject
{
    Q_OBJECT
public:
    static CourseManager theManager;
    CourseManager();
    QSet<Course> AllCourses;
    QSet<QString> AllTags;
    bool readFromFile(QFile& file);
    bool writeToFile(QFile& file);
    void generateTags();
};


#endif // COURSEMANAGER_H
