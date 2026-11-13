/*
 * DashboardView -- implementation
 *
 * TODO:
 *   - Reload from DashboardController each time the page is shown; only one
 *     user is logged in at a time.
 */

#include "dashboardview.h"
#include "ui_dashboardview.h"

DashboardView::DashboardView(DashboardController *controller, QWidget *parent)
    : QWidget(parent), controller(controller), ui(new Ui::DashboardView)
{
    // TODO: account panel, current-order panel, history table.
    ui->setupUi(this);
}

void DashboardView::displayUsername(const QString &name)
{

    ui->dashboardMainLbl->setText("Welcome " + name);

}
