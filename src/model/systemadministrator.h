/*
 * SystemAdministrator -- Model subsystem (entity class)
 *
 * One of the staff roles.
 *
 * Spec notes:
 *   - The default data has 1 system administrator. [D1 p.2 Default System
 *     Data]
 *   - D1 shows the administrator only their user type and name. [D1 p.3
 *     Feature 1]
 *   - Administrator features are excluded from D1. [D1 p.4 Excluded from
 *     this Prototype]
 */

#ifndef SYSTEMADMINISTRATOR_H
#define SYSTEMADMINISTRATOR_H

#include "staff.h"

class SystemAdministrator : public Staff
{
public:
    SystemAdministrator();
};

#endif // SYSTEMADMINISTRATOR_H
