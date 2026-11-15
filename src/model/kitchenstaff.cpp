/*
 * KitchenStaff -- implementation
 *
 * Passes the shared fields up to Staff and reports the user type.
 */

#include "kitchenstaff.h"

KitchenStaff::KitchenStaff(const QString &name, const QString &username, const QString &staffId)
    : Staff(name, username, staffId)
{
}

QString KitchenStaff::roleName() const
{
    return "Kitchen Staff";
}
