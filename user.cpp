/*
 * User -- implementation
 *
 * Shared code for all users: name and username. roleName() has no body
 * here; each role class provides its own.
 */

#include "user.h"

User::User(const QString &name, const QString &username)
    : m_name(name), m_username(username)
{
}

QString User::name() const
{
    return m_name;
}

QString User::username() const
{
    return m_username;
}
