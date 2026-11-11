/*
 * DashboardController -- Controller subsystem (control class)
 *
 * Supplies the customer dashboard: account details, current order and order
 * history.
 *
 * Spec notes:
 *   - The current order is shown while In Progress or Completed. [D1 p.3
 *     Feature 4]
 *   - The history is the last 5 orders that reached Picked Up or Cancelled.
 *     [Overview sec. 2, Online Dashboard]
 *   - Optional: update email and home address. [Overview sec. 2, Online
 *     Dashboard]
 */

#ifndef DASHBOARDCONTROLLER_H
#define DASHBOARDCONTROLLER_H

class CafeDataStore;

class DashboardController
{
public:
    DashboardController();

    // TODO: operations for the views. Pass the logged-in username in
    //       (MainWindow gets it from AccountController) and return plain
    //       data (QString, numbers), not model pointers.

private:
    CafeDataStore &store;   // Figure 1: DashboardController -> CafeDataStore
};

#endif // DASHBOARDCONTROLLER_H
