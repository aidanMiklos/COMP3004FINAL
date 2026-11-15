#ifndef MANAGER_H
#define MANAGER_H

#include "staff.h"

class Manager : public Staff
{
public:
    Manager(const QString &name,const QString &username,const QString &staffId);

    QString roleName() const override;
};

#endif // MANAGER_H
