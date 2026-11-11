/*
 * OrderItem -- Model subsystem (entity class)
 *
 * One line of an order: which MenuItem, and how many.
 *
 * Spec notes:
 *   - Order records include the items and their quantities. [Overview sec.
 *     4.3]
 *   - Each order lists the items purchased. [D1 p.2 Default System Data]
 */

#ifndef ORDERITEM_H
#define ORDERITEM_H

class MenuItem;

class OrderItem
{
public:
    OrderItem();

private:
    MenuItem *menuItem = nullptr;   // Figure 1: OrderItem -> MenuItem
};

#endif // ORDERITEM_H
