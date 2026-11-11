/*
 * DashboardView -- implementation
 *
 * TODO:
 *   - Reload from DashboardController each time the page is shown; only one
 *     user is logged in at a time.
 */

#include "dashboardview.h"

DashboardView::DashboardView(DashboardController *controller, QWidget *parent)
    : QWidget(parent), controller(controller)
{
    // TODO: account panel, current-order panel, history table.
}
