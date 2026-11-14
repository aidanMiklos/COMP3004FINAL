#ifndef CASHIER_H
#define CASHIER_H
#include "staff.h"

class Cashier : public Staff
{
public:
    Cashier(const QString &name,const QString &username,const QString &staffId);

    QString roleName() const override;
};

#endif // CASHIER_H
