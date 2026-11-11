/*
 * Manager -- Model subsystem (entity class)
 *
 * One of the staff roles.
 *
 * Spec notes:
 *   - The default data has 1 manager. [D1 p.2 Default System Data]
 *   - D1 shows the manager only their user type and name. [D1 p.3 Feature 1]
 *   - Manager features are excluded from D1. [D1 p.4 Excluded from this
 *     Prototype]
 */

#ifndef MANAGER_H
#define MANAGER_H

#include "staff.h"

class Manager : public Staff
{
public:
    Manager();
};

#endif // MANAGER_H
