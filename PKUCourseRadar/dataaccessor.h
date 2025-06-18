#ifndef DATAACCESSOR_H
#define DATAACCESSOR_H
#include "utils.h"


class DataAccessor
{
public:
    static QString userLogin(const QString& username, const QString& password);
    static bool userRegister(const QString& username, const QString& password);
    static void initManager(const QUuid& userid);
    static void saveManager(const QUuid& userid);
};

#endif // DATAACCESSOR_H
