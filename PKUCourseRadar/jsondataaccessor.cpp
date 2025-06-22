#include "jsondataaccessor.h"
#include <QCryptographicHash>
#include "course.h"
#include <QCoreApplication>

QJsonDocument JsonDataAccessor::readDatabase()
{
    QFile file(QDir(QCoreApplication::applicationDirPath()).filePath("database.json"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QJsonDocument();
    }

    QByteArray file_content = file.readAll();
    file.close();

    QJsonDocument json_doc = QJsonDocument::fromJson(file_content);
    if (json_doc.isNull()) {
        return QJsonDocument();
    }
    return json_doc;
}

bool JsonDataAccessor::writeDatabase(const QJsonDocument& doc)
{
    QFile file(QDir(QCoreApplication::applicationDirPath()).filePath("database.json"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        return false;
    }

    QByteArray json_data = doc.toJson(QJsonDocument::Indented);
    if (file.write(json_data) == -1) {
        file.close();
        return false;
    }
    file.close();
    return true;
}

QString JsonDataAccessor::userLogin(const QString& username, const QString& password)
{
    QJsonDocument doc = readDatabase();
    if (doc.isNull() || !doc.isObject()) return QString();

    QJsonObject root_obj = doc.object();
    QJsonArray users_array = root_obj["users"].toArray();

    QString password_md5 = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());

    for (const QJsonValue& user_value : users_array) {
        if (!user_value.isObject()) continue;
        QJsonObject user_obj = user_value.toObject();
        if (user_obj["username"].toString() == username &&
            user_obj["passwordmd5"].toString() == password_md5) {
            return user_obj["uuid"].toString();
        }
    }
    return QString();
}

bool JsonDataAccessor::userRegister(const QString& username, const QString& password)
{
    QJsonDocument doc = readDatabase();
    QJsonObject root_obj;

    if (doc.isNull() || !doc.isObject()) {
        root_obj["users"] = QJsonArray();
        root_obj["courses"] = QJsonArray();
        doc.setObject(root_obj);
    } else {
        root_obj = doc.object();
    }

    QJsonArray users_array = root_obj["users"].toArray();

    for (const QJsonValue& user_value : users_array) {
        if (!user_value.isObject()) continue;
        QJsonObject user_obj = user_value.toObject();
        if (user_obj["username"].toString() == username) {
            return false;
        }
    }

    QJsonObject new_user_obj;
    QUuid user_uuid = QUuid::createUuid();
    QString password_md5 = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());

    new_user_obj["username"] = username;
    new_user_obj["passwordmd5"] = password_md5;
    new_user_obj["uuid"] = user_uuid.toString(QUuid::WithoutBraces);
    new_user_obj["selected_courses"] = QJsonArray();
    new_user_obj["marked_courses"] = QJsonArray();

    users_array.append(new_user_obj);
    root_obj["users"] = users_array;
    doc.setObject(root_obj);

    return writeDatabase(doc);
}

void JsonDataAccessor::initManager(const QUuid& user_id)
{
    CourseManager::theManager.currentUserId = user_id;

    QJsonDocument doc = readDatabase();
    if (doc.isNull() || !doc.isObject()) return;

    QJsonObject root_obj = doc.object();

    QJsonArray courses_array = root_obj["courses"].toArray();
    CourseManager::theManager.AllCourses.clear();
    CourseManager::theManager.AllComments.clear();

    for (const QJsonValue& course_value : courses_array) {
        if (!course_value.isObject()) continue;
        QJsonObject course_obj = course_value.toObject();

        Course new_course;
        new_course.name = course_obj["name"].toString();
        new_course.building = course_obj["building"].toString();
        new_course.room = course_obj["room"].toString();
        new_course.teacher = course_obj["teacher"].toString();
        new_course.note = course_obj["note"].toString();
        new_course.id = QUuid(course_obj["uuid"].toString());

        QJsonArray json_course_time_array = course_obj["courseTime"].toArray();
        for (int i = 0; i < 7; ++i) {
            QJsonArray day_sessions = json_course_time_array[i].toArray();
            for (const QJsonValue& session_value : day_sessions) {
                new_course.ct.add(i + 1, session_value.toInt());
            }
        }

        QJsonArray json_tags_array = course_obj["tags"].toArray();
        for (const QJsonValue& tag_value : json_tags_array) {
            new_course.tags.insert(tag_value.toString());
        }

        QJsonArray json_comments_array = course_obj["comments"].toArray();
        for (const QJsonValue& comment_value : json_comments_array) {
            if (!comment_value.isObject()) continue;
            QJsonObject comment_obj = comment_value.toObject();
            CourseComment new_comment;
            new_comment.commentId = QUuid(comment_obj["comment_uuid"].toString());
            new_comment.courseId = QUuid(comment_obj["course_uuid"].toString());
            new_comment.commenterId = QUuid(comment_obj["user_uuid"].toString());
            new_comment.comment = comment_obj["text"].toString();
            new_comment.rating = comment_obj["rating"].toDouble();
            QJsonArray likes_array = comment_obj["likes"].toArray();
            QJsonArray dislikes_array = comment_obj["dislikes"].toArray();
            for(const QJsonValue& like_value : likes_array) {
                new_comment.likes.insert(QUuid(like_value.toString()));
            }
            for(const QJsonValue& dislike_value : dislikes_array) {
                new_comment.dislikes.insert(QUuid(dislike_value.toString()));
            }
            new_comment.commentTime = comment_obj["time"].toString().toULongLong();

            CourseManager::theManager.AllComments.insert(new_comment.commentId, new_comment);
            new_course.comments.append(new_comment.commentId);
        }

        CourseManager::theManager.AllCourses.insert(new_course.id, new_course);
    }

    QJsonArray users_array = root_obj["users"].toArray();
    for (const QJsonValue& user_value : users_array) {
        if (!user_value.isObject()) continue;
        QJsonObject user_obj = user_value.toObject();
        CourseManager::theManager.userNames[QUuid(user_obj["uuid"].toString())] = user_obj["username"].toString();
        if (QUuid(user_obj["uuid"].toString()) == user_id) {
            CourseManager::theManager.selectedCourses = QVector<QVector<QUuid>>(7, QVector<QUuid>(12, QUuid()));
            QJsonArray selected_courses_array = user_obj["selected_courses"].toArray();
            for (const QJsonValue& sc_value : selected_courses_array) {
                if (!sc_value.isObject()) continue;
                QJsonObject sc_obj = sc_value.toObject();
                int day = sc_obj["day"].toInt();
                int session = sc_obj["session"].toInt();
                QUuid course_uuid = QUuid(sc_obj["course_uuid"].toString());
                if (day >= 1 && day <= 7 && session >= 1 && session <= 12) {
                    CourseManager::theManager.selectedCourses[day - 1][session - 1] = course_uuid;
                }
            }

            for (Course& course : CourseManager::theManager.AllCourses) {
                course.marked = false;
            }
            QJsonArray marked_courses_array = user_obj["marked_courses"].toArray();
            for (const QJsonValue& mc_value : marked_courses_array) {
                QUuid course_uuid = QUuid(mc_value.toString());
                if (CourseManager::theManager.AllCourses.contains(course_uuid)) {
                    CourseManager::theManager.AllCourses[course_uuid].marked = true;
                }
            }
        }
    }


    CourseManager::theManager.generateTags();
}

void JsonDataAccessor::saveManager(const QUuid& user_id)
{
    QJsonDocument doc = readDatabase();
    QJsonObject root_obj;

    if (doc.isNull() || !doc.isObject()) {
        root_obj["users"] = QJsonArray();
        root_obj["courses"] = QJsonArray();
    } else {
        root_obj = doc.object();
    }

    QJsonArray users_array = root_obj["users"].toArray();
    for (int i = 0; i < users_array.size(); ++i) {
        QJsonObject user_obj = users_array[i].toObject();
        if (QUuid(user_obj["uuid"].toString()) == user_id) {
            QJsonArray selected_courses_json_array;
            for (int day = 0; day < 7; ++day) {
                for (int session = 0; session < 12; ++session) {
                    QUuid course_uuid = CourseManager::theManager.selectedCourses[day][session];
                    if (!course_uuid.isNull()) {
                        QJsonObject sc_obj;
                        sc_obj["day"] = day + 1;
                        sc_obj["session"] = session + 1;
                        sc_obj["course_uuid"] = course_uuid.toString(QUuid::WithoutBraces);
                        selected_courses_json_array.append(sc_obj);
                    }
                }
            }
            user_obj["selected_courses"] = selected_courses_json_array;

            QJsonArray marked_courses_json_array;
            for (const Course& course : CourseManager::theManager.AllCourses.values()) {
                if (course.marked) {
                    marked_courses_json_array.append(course.id.toString(QUuid::WithoutBraces));
                }
            }
            user_obj["marked_courses"] = marked_courses_json_array;

            users_array[i] = user_obj;
            break;
        }
    }
    root_obj["users"] = users_array;

    QJsonArray courses_json_array;
    for (const Course& course : CourseManager::theManager.AllCourses.values()) {
        QJsonObject course_obj;
        course_obj["name"] = course.name;
        course_obj["building"] = course.building;
        course_obj["room"] = course.room;
        course_obj["teacher"] = course.teacher;
        course_obj["note"] = course.note;
        course_obj["uuid"] = course.id.toString(QUuid::WithoutBraces);

        QJsonArray course_time_json_array;
        for (int day = 0; day < 7; ++day) {
            QJsonArray sessions_json_array;
            for (int session = 0; session < 12; ++session) {
                if (course.ct.table[day][session]) {
                    sessions_json_array.append(session + 1);
                }
            }
            course_time_json_array.append(sessions_json_array);
        }
        course_obj["courseTime"] = course_time_json_array;

        QJsonArray tags_json_array;
        for (const QString& tag : course.tags) {
            tags_json_array.append(tag);
        }
        course_obj["tags"] = tags_json_array;

        QJsonArray comments_json_array;
        for (const QUuid& comment_uuid : course.comments) {
            if (CourseManager::theManager.AllComments.contains(comment_uuid)) {
                const CourseComment& comment = CourseManager::theManager.AllComments[comment_uuid];
                QJsonObject comment_obj;
                comment_obj["comment_uuid"] = comment.commentId.toString(QUuid::WithoutBraces);
                comment_obj["user_uuid"] = comment.commenterId.toString(QUuid::WithoutBraces);
                comment_obj["course_uuid"] = comment.courseId.toString(QUuid::WithoutBraces);
                comment_obj["text"] = comment.comment;
                comment_obj["rating"] = comment.rating;
                QJsonArray likes_json_array;
                for(const QUuid& like_uuid : comment.likes) {
                    likes_json_array.append(like_uuid.toString(QUuid::WithoutBraces));
                }
                comment_obj["likes"] = likes_json_array;
                QJsonArray dislikes_json_array;
                for(const QUuid& dislike_uuid : comment.dislikes) {
                    dislikes_json_array.append(dislike_uuid.toString(QUuid::WithoutBraces));
                }
                comment_obj["dislikes"] = dislikes_json_array;
                comment_obj["time"] = QString::number(comment.commentTime);
                comments_json_array.append(comment_obj);
            }
        }
        course_obj["comments"] = comments_json_array;

        courses_json_array.append(course_obj);
    }
    root_obj["courses"] = courses_json_array;

    doc.setObject(root_obj);
    writeDatabase(doc);
}

