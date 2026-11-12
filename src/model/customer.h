/*
 * Customer -- Model subsystem (entity class)
 *
 * A customer account. Holds the current order and the order history (Figure
 * 1: Customer -- Order).
 *
 * Spec notes:
 *   - Name, unique username, unique loyalty points number, email, home
 *     address, loyalty points balance and account credit balance. [D1 p.2
 *     Default System Data]
 *   - Each customer has 5 orders in their history. [D1 p.2 Default System
 *     Data]
 *   - Only one current order at a time. [D1 p.3-4 Business Rules]
 *   - Account credit is money returned when an online order is cancelled,
 *     usable on later orders. [Overview sec. 2, Ordering Application]
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QList>

#include "user.h"

class Order;

class Customer : public User
{
public:
    Customer();
    ~Customer() override;

    Customer(const Customer &) = delete;
    Customer &operator=(const Customer &) = delete;

private:
    // A customer owns all of its orders; OrderQueue only points to them.
    Order *currentOrder = nullptr;   // Figure 1: Customer -- Order (at most one)
    QList<Order *> history;          // Figure 1: Customer -- Order (last 5)
};

#endif // CUSTOMER_H
