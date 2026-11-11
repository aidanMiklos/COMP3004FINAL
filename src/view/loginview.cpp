/*
 * LoginView -- implementation
 *
 * TODO:
 *   - On submit, ask AccountController to identify the user; show an error
 *     if there is no match, otherwise let MainWindow switch to that user's
 *     interface. [D1 p.2-3 Feature 1]
 */

#include "loginview.h"

LoginView::LoginView(AccountController *controller, QWidget *parent)
    : QWidget(parent), controller(controller)
{
    // TODO: name/username field, Enter button, error label.
}
