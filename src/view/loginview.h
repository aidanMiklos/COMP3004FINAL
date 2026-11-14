/*
 * LoginView -- View subsystem (boundary class)
 *
 * Startup form and first page of MainWindow. Takes a name or username and
 * asks AccountController who it belongs to.
 *
 * Spec notes:
 *   - Users enter their name or username on the startup form; the system
 *     checks it against the in-memory data and shows the interface for their
 *     user type. This is identification only, not real authentication. [D1
 *     p.2-3 Feature 1]
 *   - The README must list the account names or usernames of all 11 default
 *     users for testing. [D1 p.4-5 Submission Requirements]
 */

#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginView; }
QT_END_NAMESPACE

class AccountController;

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(AccountController *controller, QWidget *parent = nullptr);

private:
    AccountController *controller;   // Figure 1: LoginView -> AccountController

    Ui::LoginView *ui;
};

#endif // LOGINVIEW_H
