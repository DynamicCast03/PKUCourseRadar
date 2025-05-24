#include "coursemanager.h"


CourseManager CourseManager::theManager;

CourseManager::CourseManager() {
    
}

bool CourseManager::readFromFile(QFile& file)
{
    AllCourses.clear();
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray fileContent = file.readAll();
    file.close();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileContent);
    if (!jsonDoc.isArray()) return false;
    QJsonArray jsonCoursesArray = jsonDoc.array();
    for (const QJsonValue& courseValue : jsonCoursesArray) {
        if (!courseValue.isObject()) return false;
        QJsonObject courseObject = courseValue.toObject();
        QString name = courseObject["name"].toString();
        QString building = courseObject["building"].toString();
        QString room = courseObject["room"].toString();
        QString teacher = courseObject["teacher"].toString();
        QString note = courseObject["note"].toString();
        CourseTime courseTime;
        if (courseObject.contains("courseTime") && courseObject["courseTime"].isArray()) {
            QJsonArray jsonCourseTimeArray = courseObject["courseTime"].toArray();
            if (jsonCourseTimeArray.size() == 7) {
                for (int i = 0; i < 7; i++) {
                    if (jsonCourseTimeArray[i].isArray()) {
                        QJsonArray jsonSessionsArray = jsonCourseTimeArray[i].toArray();
                        for (const QJsonValue& sessionValue : jsonSessionsArray) {
                            if (sessionValue.isDouble()) {
                                int session = sessionValue.toInt();
                                if (session >= 1 && session <= 12) {
                                    courseTime.add(i + 1, session);
                                } else return false;
                            } else return false;
                        }
                    } else return false;
                }
            } else return false;
        } else return false;
        QSet<QString> tags;
        if (courseObject.contains("tags") && courseObject["tags"].isArray()) {
            QJsonArray jsonTagsArray = courseObject["tags"].toArray();
            for (const QJsonValue& tagValue : jsonTagsArray) {
                if (tagValue.isString()) {
                    tags.insert(tagValue.toString());
                } else return false;
            }
        } else return false;
        Course newCourse;
        newCourse.name = name;
        newCourse.building = building;
        newCourse.room = room;
        newCourse.teacher = teacher;
        newCourse.ct = courseTime;
        newCourse.tags = tags;
        newCourse.note = note;
        if(AllCourses.find(newCourse) != AllCourses.end()) return false;
        AllCourses.insert(newCourse);
    }
    generateTags();
    return true;
}

bool CourseManager::writeToFile(QFile& file)
{
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) return false;
    QJsonArray jsonCoursesArray;
    for (const Course& course : AllCourses) {
        QJsonObject courseObject;
        courseObject["name"] = course.name;
        courseObject["room"] = course.room;
        courseObject["building"] = course.building;
        courseObject["teacher"] = course.teacher;
        courseObject["note"] = course.note;
        QJsonArray jsonCourseTimeArray;
        for (int i = 0; i < 7; i++) {
            QJsonArray jsonSessionsArray;
            for (int j = 0; j < 12; j++) {
                if (course.ct.table[i][j]) {
                    jsonSessionsArray.append(j + 1);
                }
            }
            jsonCourseTimeArray.append(jsonSessionsArray);
        }
        courseObject["courseTime"] = jsonCourseTimeArray;
        QJsonArray jsonTagsArray;
        for (const QString& tag : course.tags) {
            jsonTagsArray.append(tag);
        }
        courseObject["tags"] = jsonTagsArray;
        jsonCoursesArray.append(courseObject);
    }
    QJsonDocument jsonDoc(jsonCoursesArray);
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Indented);
    if (file.write(jsonData) == -1) {
        file.close();
        return false;
    }
    file.close();
    return true;
}

void CourseManager::generateTags() {
    for (const Course& course : AllCourses) {
        for (const QString& tag : course.tags) {
            AllTags.insert(tag);
        }
    }
}