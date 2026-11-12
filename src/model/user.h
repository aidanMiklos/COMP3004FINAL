/*
 * User -- Model subsystem (entity class)
 *
 * Abstract base for every user. Each role overrides roleName(), and the user
 * type it returns decides which interface opens after login (polymorphism).
 *
 * Spec notes:
 *   - Every user has a name and a unique username. [D1 p.2 Default System
 *     Data]
 *   - User types: Customer, Kitchen Staff, Cashier, Manager, System
 *     Administrator. [D1 p.2-3 Feature 1]
 */

#ifndef USER_H
#define USER_H

#include <QString>

class User
{
    public:
        virtual ~User() = default;

        QString name() const;
        QString username() const;

        // The user role (customer, Kitchen Staff, etc), tbd by the subclass       
        virtual QString roleName() const = 0;

    protected:
        User(const QString &name, const QString &username);   // only subclasses

    private:
        QString m_name;
        QString m_username;
};

#endif // USER_H
