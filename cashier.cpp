#include "cashier.h"

Cashier::Cashier(const QString &name,const QString &username,const QString &staffId):
    Staff(name, username, staffId)
{
}

QString Cashier::roleName()const{
    return "Cashier";
}
