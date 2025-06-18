#ifndef JSONDATAACCESSOR_H
#define JSONDATAACCESSOR_H

#include "dataaccessor.h"
#include "coursemanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QVector>
#include <QMap>
#include <QSet>
#include <QUuid>

class JsonDataAccessor
{
public:
    static QString userLogin(const QString& username, const QString& password);
    static bool userRegister(const QString& username, const QString& password);
    static void initManager(const QUuid& user_id);
    static void saveManager(const QUuid& user_id);

private:
    static QJsonDocument readDatabase();
    static bool writeDatabase(const QJsonDocument& doc);
    static const QString database_file_path_;
};

#endif // JSONDATAACCESSOR_H 
