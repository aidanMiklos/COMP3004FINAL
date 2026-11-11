/*
 * Staff -- Model subsystem (entity class)
 *
 * Abstract base for the four staff roles.
 *
 * Spec notes:
 *   - Every staff member has a name, unique username and unique staff ID.
 *     [D1 p.2 Default System Data]
 *   - Staff log in with an account that has a unique staff ID; in D1 they
 *     are identified by name or username. [Overview sec. 2, Staff sections;
 *     D1 p.2-3 Feature 1]
 */

#ifndef STAFF_H
#define STAFF_H

#include "user.h"

class Staff : public User
{
public:

protected:
    Staff() = default;   // abstract: only subclasses are created
};

#endif // STAFF_H
