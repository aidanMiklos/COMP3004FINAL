/*
 * AccountController -- implementation
 *
 * TODO:
 *   - identify(): look the name or username up through CafeDataStore and
 *     remember the username. [D1 p.2-3 Feature 1]
 *   - logout(): clear the remembered username. [D1 p.3 Feature 1]
 */

#include "accountcontroller.h"

#include "cafedatastore.h"
#include "user.h"

AccountController::AccountController()
    : store(CafeDataStore::instance())
{
}

bool AccountController::identify(const QString &nameOrUsername)
{
    logout();

    const QString entered = nameOrUsername.trimmed();
    if (entered.isEmpty())
        return false;

    User *user = store.findUser(entered);
    if (!user)
        return false;

    m_currentUsername = user->username();
    return true;
}

void AccountController::logout()
{
    m_currentUsername.clear();
}

bool AccountController::isLoggedIn() const
{
    return !m_currentUsername.isEmpty();
}

QString AccountController::currentUsername() const
{
    return m_currentUsername;
}

QString AccountController::currentName() const
{
    User *user = currentUser();
    return user ? user->name() : QString();
}

QString AccountController::currentRole() const
{
    User *user = currentUser();
    return user ? user->roleName() : QString();
}

User *AccountController::currentUser() const
{
    return isLoggedIn() ? store.findUser(m_currentUsername) : nullptr;
}
