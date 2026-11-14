/*
 * MainWindow -- View subsystem (boundary class)
 *
 * The single top-level window. Holds the pages below as a stack, shows a
 * header with the logged-in user's role and name, shows only that role's
 * menu, and has File > Log out. Talks to AccountController for who is logged
 * in (Figure 1).
 *
 * Spec notes:
 *   - The GUI is built with Qt widgets, and features are reached through
 *     menu items, dialog boxes or pop-up menus. [D1 p.4 Implementation
 *     Requirements; Overview sec. 4.1]
 *   - The interface makes each role obvious and keeps navigation,
 *     terminology and the placement of shared controls the same across
 *     roles. [D1 p.4 Implementation Requirements]
 *   - Cashier, Manager and System Administrator see only their user type and
 *     name, with no other features. [D1 p.3 Feature 1]
 *   - Exiting returns to the startup form and clears the previous user's
 *     data. [D1 p.3 Feature 1]
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class AccountController;
class DashboardController;
class KitchenController;
class MenuController;
class OrderController;

class DashboardView;
class LoginView;
class MakeOrderView;
class MenuView;
class OrderQueueView;

class QStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(AccountController *accounts, MenuController *menu,
               OrderController *orders, DashboardController *dashboard,
               KitchenController *kitchen, QWidget *parent = nullptr);

private:
    AccountController *accountController;   // Figure 1: MainWindow -> AccountController

    QStackedWidget *widgetStack;

    // Pages (Figure 1: MainWindow -> each page)
    LoginView *loginView;
    MenuView *menuView;
    MakeOrderView *makeOrderView;
    DashboardView *dashboardView;
    OrderQueueView *orderQueueView;

    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
