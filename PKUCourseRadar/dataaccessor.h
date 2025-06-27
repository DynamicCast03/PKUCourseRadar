#ifndef DATAACCESSOR_H
#define DATAACCESSOR_H
#include "utils.h"


class DataAccessor
{
public:
    static DataAccessor* theDataAccessor;
    virtual QString userLogin(const QString& username, const QString& password) = 0;
    virtual bool userRegister(const QString& username, const QString& password) = 0;
    virtual void initManager(const QUuid& userid) = 0;
    virtual void saveManager(const QUuid& userid) = 0;
};

#endif // DATAACCESSOR_H
