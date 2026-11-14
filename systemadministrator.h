#ifndef SYSTEMADMINISTRATOR_H
#define SYSTEMADMINISTRATOR_H
#include "staff.h"

class SystemAdministrator : public Staff
{
public:
    SystemAdministrator(const QString &name,const QString &username,const QString &staffId);

    QString roleName() const override;
};

#endif // SYSTEMADMINISTRATOR_H
