#include "coursemanager.h"


CourseManager CourseManager::theManager;

CourseManager::CourseManager() {
    selectedCourses = QVector<QVector<QUuid>>(7, QVector<QUuid>(12, QUuid()));
}

void CourseManager::generateTags() {
    AllTags.clear();
    for (const Course& course : AllCourses.values()) {
        for (const QString& tag : course.tags) {
            AllTags.insert(tag);
        }
    }
}

QUuid& CourseManager::getSelectedCourse(int day, int session) {
    return selectedCourses[day - 1][session - 1];
}

CourseComment::CourseComment()
    :commentId(),
    courseId(),
    commenterId()
{
}

CourseComment::CourseComment(const CourseComment& cc){
    commentId = cc.commentId;
    courseId = cc.courseId;
    comment = cc.comment;
    commenterId = cc.commenterId;
    commentTime = cc.commentTime;
    rating = cc.rating;
    likes = cc.likes;
    dislikes = cc.dislikes;
}

CourseComment& CourseComment::operator=(const CourseComment& cc){
    commentId = cc.commentId;
    courseId = cc.courseId;
    comment = cc.comment;
    commenterId = cc.commenterId;
    commentTime = cc.commentTime;
    rating = cc.rating;
    likes = cc.likes;
    dislikes = cc.dislikes;
}


QString CourseComment::format(){
    return tr("评论者: %1\n时间: %2\n评分: %3\n------------------------------\n%4").arg(CourseManager::theManager.userNames[commenterId]).arg(QDateTime::fromSecsSinceEpoch(commentTime).toString("yyyy-MM-dd hh:mm:ss")).arg(rating, 0, 'f', 1).arg(comment);
}
