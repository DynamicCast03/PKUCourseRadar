#ifndef COURSEMANAGER_H
#define COURSEMANAGER_H

#include "utils.h"
#include "course.h"

class CourseComment{
public:
    QUuid commentId;
    QUuid courseId;
    QString comment;
    QUuid commenterId;
    unsigned long long commentTime;
    double rating;
    int likes;
    int dislikes;
};

class CourseManager : public QObject
{
    Q_OBJECT
public:
    static CourseManager theManager;
    CourseManager();
    QMap<QUuid, Course> AllCourses;
    QSet<QString> AllTags;
    QMap<QUuid, CourseComment> AllComments;
    bool readFromFile(QFile& file);
    bool writeToFile(QFile& file);
    void generateTags();
    QUuid& getSelectedCourse(int day, int session);
    QVector<QVector<QUuid>> selectedCourses;
};


#endif // COURSEMANAGER_H
