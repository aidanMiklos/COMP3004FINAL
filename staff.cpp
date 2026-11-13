/*
 * Staff -- implementation
 *
 *   - Shared code for staff (staff ID).
 */

#include "staff.h"

Staff::Staff(const QString &name, const QString &username, const QString &staffId)
    : User(name, username), m_staffId(staffId)
{
}

QString Staff::staffId() const
{
    return m_staffId;
}
