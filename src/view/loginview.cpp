/*
 * LoginView -- implementation
 *
 * TODO:
 *   - On submit, ask AccountController to identify the user; show an error
 *     if there is no match, otherwise let MainWindow switch to that user's
 *     interface. [D1 p.2-3 Feature 1]
 */

#include "loginview.h"
#include "ui_loginview.h"
#include "viewtype.h"

LoginView::LoginView(AccountController *controller, QWidget *parent)
    : QWidget(parent), controller(controller), ui(new Ui::LoginView)
{
    // TODO: name/username field, Enter button, error label.
    ui->setupUi(this);

    connect(ui->signinBtn, &QPushButton::clicked, this, &LoginView::signinBtnClicked);
}

// ----------------- PUBLIC SLOTS -----------------

void LoginView::errorSignInUnsuccessful(const QString &message)
{
    // If there is an error with sign-in, we display the error message to the user
    ui->loginWarningLbl->setText(message);
}

void LoginView::signinSuccessful()
{
    // If a sign in is successful, we emit requestViewChange so the mainwindow will swap the view
    emit requestViewChange(ViewType::DashboardView);
}

// ----------------- PRIVATE SLOTS -----------------

void LoginView::signinBtnClicked()
{
    // If the sign in button is clicked, we simply emit what the user has provided in the text box
    emit userSignIn(ui->usernameInput->text());
//    emit requestViewChange(ViewType::DashboardView);
}


