#include "course.h"
#include "utils.h"
#include "coursemanager.h"

Course::Course() { }

Course::Course(const Course& c)
{
    ct = c.ct;
    id = c.id;
    name = c.name;
    building = c.building;
    room = c.room;
    teacher = c.teacher;
    tags = c.tags;
    comments = c.comments;
    note = c.note;
    marked = c.marked;
}

Course& Course::operator=(const Course& c)
{
    ct = c.ct;
    id = c.id;
    name = c.name;
    building = c.building;
    room = c.room;
    teacher = c.teacher;
    tags = c.tags;
    comments = c.comments;
    note = c.note;
    marked = c.marked;
    return *this;
}

QString Course::description()
{
    return tr("课程名称：%1\n"
              "上课时间：\n%2"
              "上课地点：%3\n"
              "授课教师：%4\n"
              "课程标签：%5\n"
              "课程平均评分：%6\n"
              "课程备注：%7")
        .arg(name).arg(ct.toString()).arg(building + " " + room).arg(teacher).arg(tagsString()).arg(rating()).arg(note);
}

QString Course::tagsString()
{
    if (tags.empty())
        return "";
    QString ans;
    for (const auto& tag : tags) {
        if (ans != "")
            ans += ", ";
        ans += tag;
    }
    return ans;
}

bool Course::include(int day, int session) const
{
    return ct.table[day - 1][session - 1] != 0;
}

double Course::rating(){
    if(comments.size() == 0) return 4.2;
    double sum = 0;
    for(QUuid commentId : comments){
        sum += CourseManager::theManager.AllComments[commentId].rating;
    }
    return sum / comments.size();
}
