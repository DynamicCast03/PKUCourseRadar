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

class JsonDataAccessor : public DataAccessor
{
public:
    QString userLogin(const QString& username, const QString& password);
    bool userRegister(const QString& username, const QString& password);
    void initManager(const QUuid& user_id);
    void saveManager(const QUuid& user_id);

private:
    QJsonDocument readDatabase();
    bool writeDatabase(const QJsonDocument& doc);
    const QString database_file_path_;
};

#endif // JSONDATAACCESSOR_H 
