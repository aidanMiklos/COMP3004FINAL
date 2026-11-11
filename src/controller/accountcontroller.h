/*
 * AccountController -- Controller subsystem (control class)
 *
 * Identifies the user, remembers who is logged in, and logs out. Used by
 * LoginView and MainWindow. It keeps only the username, not a User pointer,
 * so it has no line to User in Figure 1.
 *
 * Spec notes:
 *   - Check the entered name or username against the in-memory users and
 *     report the user type. [D1 p.2-3 Feature 1]
 *   - Logging out clears the previous user's data so nothing carries over.
 *     [D1 p.3 Feature 1]
 *   - Session timeout is excluded from D1. [D1 p.4 Excluded from this
 *     Prototype]
 */

#ifndef ACCOUNTCONTROLLER_H
#define ACCOUNTCONTROLLER_H

#include <QString>

class CafeDataStore;

class AccountController
{
public:
    AccountController();

    // TODO: operations for the views. Pass the logged-in username in
    //       (MainWindow gets it from AccountController) and return plain
    //       data (QString, numbers), not model pointers.

private:
    CafeDataStore &store;   // Figure 1: AccountController -> CafeDataStore
    QString currentUsername;   // empty when nobody is logged in
};

#endif // ACCOUNTCONTROLLER_H
