/*
 * main.cpp -- program entry point
 *
 * Creates one of each controller for the whole run and the MainWindow, then
 * starts the Qt event loop. The default data is loaded the first time
 * CafeDataStore is used.
 *
 * Spec notes:
 *   - The system runs on a single host. [D1 p.4 Implementation Requirements]
 *   - The TA extracts the zip, opens the .pro file in Qt Creator, and builds
 *     and runs it on the course VM in under three minutes without changing
 *     paths or settings. [D1 p.4 Submission Requirements]
 *   - The default menu, users and order histories are loaded at startup. [D1
 *     p.1-2 Default System Data]
 */

#include <QApplication>

#include "accountcontroller.h"
#include "dashboardcontroller.h"
#include "kitchencontroller.h"
#include "mainwindow.h"
#include "menucontroller.h"
#include "ordercontroller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // One of each controller for the whole run; each reaches the data only
    // through CafeDataStore (Figure 1).
    AccountController accounts;
    MenuController menu;
    OrderController orders;
    DashboardController dashboard;
    KitchenController kitchen;

    MainWindow window(&accounts, &menu, &orders, &dashboard, &kitchen);
    window.show();

    return app.exec();
}
