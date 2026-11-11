/*
 * OrderQueueView -- View subsystem (boundary class)
 *
 * Kitchen page listing the orders waiting to be prepared. Opens
 * OrderDetailsView for the selected order (Figure 1: OrderQueueView ->
 * OrderDetailsView).
 *
 * Spec notes:
 *   - For each order in the queue, show the order number, customer name, and
 *     order date and time. [D1 p.3 Feature 5]
 *   - Orders are shown first-in, first-out. [Overview sec. 2, Order Queue
 *     Process]
 *   - Dates with times use the format YYYY-MM-DD:HH:MM. [Overview sec. 4.2]
 */

#ifndef ORDERQUEUEVIEW_H
#define ORDERQUEUEVIEW_H

#include <QWidget>

class KitchenController;
class OrderDetailsView;

class OrderQueueView : public QWidget
{
    Q_OBJECT

public:
    explicit OrderQueueView(KitchenController *controller, QWidget *parent = nullptr);

private:
    KitchenController *controller;   // Figure 1: OrderQueueView -> KitchenController
    OrderDetailsView *detailsDialog;   // Figure 1: OrderQueueView -> OrderDetailsView
};

#endif // ORDERQUEUEVIEW_H
