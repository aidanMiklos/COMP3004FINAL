/*
 * KitchenStaff -- Model subsystem (entity class)
 *
 * One of the staff roles.
 *
 * Spec notes:
 *   - The default data has 2 kitchen staff. [D1 p.2 Default System Data]
 *   - Kitchen staff can use the queue features after identification. [D1
 *     p.2-3 Feature 1]
 */

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
