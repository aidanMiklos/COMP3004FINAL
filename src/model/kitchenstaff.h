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

#include "staff.h"

class KitchenStaff : public Staff
{
public:
    KitchenStaff();
};

#endif // KITCHENSTAFF_H
