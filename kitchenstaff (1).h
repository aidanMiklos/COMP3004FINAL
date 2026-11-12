#ifndef KITCHENSTAFF_H
#define KITCHENSTAFF_H

#include <QString>

#include "staff.h"

class KitchenStaff : public Staff
{
public:
    KitchenStaff(const QString &name, const QString &username, const QString &staffId);

    QString roleName() const override;   // Override the User roleName() function to return this specific one
};

#endif // KITCHENSTAFF_H
