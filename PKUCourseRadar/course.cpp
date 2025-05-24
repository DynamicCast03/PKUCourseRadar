#include "course.h"
#include "utils.h"

Course::Course() {}

Course::Course(const Course& c){
    name = c.name;
    ct = c.ct;
    building = c.building;
    room = c.room;
    teacher = c.teacher;
    tags = c.tags;
    note = c.note;
}


Course& Course::operator=(const Course& c){
    name = c.name;
    ct = c.ct;
    building = c.building;
    room = c.room;
    teacher = c.teacher;
    tags = c.tags;
    note = c.note;
    return *this;
}

QString Course::description()
{
    return tr("课程名称：%1\n"
                   "上课时间：\n%2"
                   "上课地点：%3\n"
                   "授课教师：%4\n"
                   "课程标签：%5\n"
                   "课程备注：%6")
        .arg(name, ct.toString(), building + " " + room, teacher, tagsString(), note);
}

QString Course::tagsString()
{
    if(tags.empty()) return "";
    QString ans;
    for(const auto& tag : tags) {
        if(ans != "") ans += ", ";
        ans += tag;
    }
    return ans;
}
