/*
 * Cashier -- Model subsystem (entity class)
 *
 * One of the staff roles.
 *
 * Spec notes:
 *   - The default data has 2 cashiers. [D1 p.2 Default System Data]
 *   - D1 shows a cashier only their user type and name. [D1 p.3 Feature 1]
 *   - Cashier features (in-person orders, Picked Up) are excluded from D1.
 *     [D1 p.4 Excluded from this Prototype]
 */

#ifndef CASHIER_H
#define CASHIER_H

#include "staff.h"

class Cashier : public Staff
{
public:
    Cashier();
};

#endif // CASHIER_H
