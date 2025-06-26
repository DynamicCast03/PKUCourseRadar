#ifndef COURSEMANAGER_H
#define COURSEMANAGER_H

#include "utils.h"
#include "course.h"

class CourseComment : public QObject{
    Q_OBJECT
public:
    CourseComment();
    CourseComment(const CourseComment& cc);
    CourseComment& operator=(const CourseComment& cc);
    QString format();
    QUuid commentId;
    QUuid courseId;
    QString comment;
    QUuid commenterId;
    unsigned long long commentTime;
    double rating;
    QSet<QUuid> likes; // user uuid
    QSet<QUuid> dislikes; // user uuid
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
    void generateTags();
    QUuid& getSelectedCourse(int day, int session);
    QVector<QVector<QUuid>> selectedCourses;
    QMap<QUuid, QString> userNames;
    QUuid currentUserId;
};


#endif // COURSEMANAGER_H
