#include "manager.h"


Manager::Manager(const QString &name,const QString &username,const QString &staffId):
    Staff(name, username, staffId)
{
}

QString Manager::roleName()const{
    return "Manager";
}

