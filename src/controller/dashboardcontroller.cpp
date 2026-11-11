/*
 * DashboardController -- implementation
 *
 * TODO:
 *   - Look up the logged-in customer through CafeDataStore and return
 *     display data. [D1 p.3 Feature 4]
 */

#include "dashboardcontroller.h"

#include "cafedatastore.h"

DashboardController::DashboardController()
    : store(CafeDataStore::instance())
{
}
