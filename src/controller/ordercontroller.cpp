/*
 * OrderController -- implementation
 *
 * TODO:
 *   - Before starting or submitting, check whether the customer already has
 *     a current order. [D1 p.3-4 Business Rules]
 *   - Submit: take points and credit from the Customer, set the amount
 *     charged, mark it paid, set In Progress and the date/time, add it to
 *     the OrderQueue, and make it the customer's current order. [D1 p.3-4
 *     Business Rules; Overview sec. 3]
 *   - The pricing maths lives in Order (see order.cpp), not here.
 */

#include "ordercontroller.h"

#include "cafedatastore.h"
#include "order.h"

OrderController::OrderController()
    : store(CafeDataStore::instance())
{
}

OrderController::~OrderController()
{
    delete draftOrder;
}
