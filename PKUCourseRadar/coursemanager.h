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
    QMap<QUuid, Course> AllCourses;
    QSet<QString> AllTags;
    bool readFromFile(QFile& file);
    bool writeToFile(QFile& file);
    void generateTags();
    QUuid& getSelectedCourse(int day, int session);
private:
    QVector<QVector<QUuid>> selectedCourses;
};


#endif // COURSEMANAGER_H
