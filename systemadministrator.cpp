#include "systemadministrator.h"

SystemAdministrator::SystemAdministrator(const QString &name,const QString &username,const QString &staffId):
    Staff(name, username, staffId)
{
}

QString SystemAdministrator::roleName()const{
    return "SystemAdministrator";
}

