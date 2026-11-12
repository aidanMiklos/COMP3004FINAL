/*
 * Order -- Model subsystem (entity class)
 *
 * One order. Holds its OrderItems and knows its Customer (Figure 1). The
 * pricing and loyalty rules live here so they are written once.
 *
 * Spec notes:
 *   - Order number, items, final price with tax, amount charged, points
 *     used, credit used, points earned, status, and online or in person. [D1
 *     p.2 Default System Data]
 *   - An order record also has items and quantities, tax and payment status.
 *     [Overview sec. 4.3]
 *   - States: In Progress, Completed, Picked Up; online orders may be
 *     Cancelled; no going backwards. D1 uses only In Progress to Completed.
 *     [Overview sec. 3; D1 p.3-4 Business Rules]
 *   - The order date and time use the format YYYY-MM-DD:HH:MM. [Overview
 *     sec. 4.2]
 */

#ifndef ORDER_H
#define ORDER_H

#include <QList>

class Customer;
class OrderItem;

class Order
{
public:
    Order();
    ~Order();

    Order(const Order &) = delete;
    Order &operator=(const Order &) = delete;

private:
    Customer *customer = nullptr;   // Figure 1: Customer -- Order (queue shows the name)
    QList<OrderItem *> items;       // Figure 1: Order -> OrderItem (owned)
};

#endif // ORDER_H
