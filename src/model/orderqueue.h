/*
 * OrderQueue -- Model subsystem (entity class)
 *
 * The kitchen's queue of paid orders waiting to be prepared, oldest first.
 *
 * Spec notes:
 *   - Once paid, an order joins the kitchen queue with status In Progress.
 *     [Overview sec. 2, Order Queue Process]
 *   - Orders are shown first-in, first-out. [Overview sec. 2, Order Queue
 *     Process]
 *   - A completed order leaves the queue. [Overview sec. 2, Order Queue
 *     Process]
 *   - The queue is empty whenever the program starts. [D1 p.2 Restart rules]
 */

#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

#include <QList>

class Order;

class OrderQueue
{
public:
    OrderQueue();

private:
    QList<Order *> orders;   // Figure 1: OrderQueue -> Order (oldest first, not owned)
};

#endif // ORDERQUEUE_H
