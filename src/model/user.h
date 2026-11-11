/*
 * User -- Model subsystem (entity class)
 *
 * Abstract base for every user. The user type decides which interface opens
 * after login (plan: virtual roleName()).
 *
 * Spec notes:
 *   - Every user has a name and a unique username. [D1 p.2 Default System
 *     Data]
 *   - User types: Customer, Kitchen Staff, Cashier, Manager, System
 *     Administrator. [D1 p.2-3 Feature 1]
 */

#ifndef USER_H
#define USER_H

class User
{
public:
    virtual ~User() = default;

protected:
    User() = default;   // abstract: only subclasses are created
};

#endif // USER_H
