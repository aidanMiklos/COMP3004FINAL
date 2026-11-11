/*
 * KitchenController -- implementation
 *
 * TODO:
 *   - Complete: tell the Order it is completed (which credits the customer's
 *     earned points), then remove it from the OrderQueue. [Overview sec. 3;
 *     D1 p.3 Feature 7]
 */

#include "kitchencontroller.h"

#include "cafedatastore.h"

KitchenController::KitchenController()
    : store(CafeDataStore::instance())
{
}
