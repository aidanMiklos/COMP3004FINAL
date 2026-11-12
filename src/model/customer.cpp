/*
 * Customer -- implementation
 *
 * TODO:
 *   - Balance changes live here: spend and add loyalty points and account
 *     credit. [Overview sec. 3]
 */

#include "customer.h"

#include <QtAlgorithms>

#include "order.h"

Customer::Customer() = default;

Customer::~Customer()
{
    delete currentOrder;
    qDeleteAll(history);
}
