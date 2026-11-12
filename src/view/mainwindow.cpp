/*
 * MainWindow -- implementation
 *
 * TODO:
 *   - Put the pages in a QStackedWidget with LoginView first.
 *   - After login: header shows '<role>: <name>', and only the Customer or
 *     Kitchen menu is visible (neither for cashier, manager or
 *     administrator). [D1 p.3 Feature 1]
 *   - Log out: tell AccountController, clear every page, switch back to
 *     LoginView. [D1 p.3 Feature 1]
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dashboardview.h"
#include "loginview.h"
#include "makeorderview.h"
#include "menuview.h"
#include "orderqueueview.h"
#include <QStackedWidget>

MainWindow::MainWindow(AccountController *accounts, MenuController *menu,
                       OrderController *orders, DashboardController *dashboard,
                       KitchenController *kitchen, QWidget *parent)
    : QMainWindow(parent),
      accountController(accounts),
      loginView(new LoginView(accounts, this)),
      menuView(new MenuView(menu, this)),
      makeOrderView(new MakeOrderView(orders, menu, this)),
      dashboardView(new DashboardView(dashboard, this)),
      orderQueueView(new OrderQueueView(kitchen, this)),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("DragonEndPOS");
    // TODO: stack the pages, add the header label, the role menus and File > Log out.

    widgetStack = ui->stackedWidget;

    widgetStack->addWidget(loginView);
    widgetStack->addWidget(dashboardView);
    widgetStack->addWidget(makeOrderView);
    widgetStack->addWidget(orderQueueView);
    widgetStack->addWidget(menuView);

    widgetStack->setCurrentWidget(dashboardView);

}
