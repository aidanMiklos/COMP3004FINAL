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
#include <QString>

#include "viewtype.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginView; }
QT_END_NAMESPACE

class AccountController;

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(AccountController *controller, QWidget *parent = nullptr);

// Used to notify others of stuff that has occurred
signals:
    // Signal for AccountController about an attempted sign in
    void userSignIn(const QString &username);

    // Signal for MainWindow to request the view be swapped
    void requestViewChange(ViewType requestedView);

// Used to receive signals from the controller
public slots:
    // Receives an error message from the AccountController if the client's username was incorrect
    void errorSignInUnsuccessful(const QString &message);

    // Receives a signal from the AccountController that a sign in was successful
    void signinSuccessful();

private:
    AccountController *controller;   // Figure 1: LoginView -> AccountController

    Ui::LoginView *ui;

// Used to receive signals from this view's own widgets
private slots:
    void signinBtnClicked();
};

#endif // LOGINVIEW_H
