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
#include "viewtype.h"

QT_BEGIN_NAMESPACE
namespace Ui { class OrderQueueView; }
QT_END_NAMESPACE

class KitchenController;
class OrderDetailsView;

class OrderQueueView : public QWidget
{
    Q_OBJECT

public:
    explicit OrderQueueView(KitchenController *controller, QWidget *parent = nullptr);

signals:

    // Signal for MainWindow to request the view be swapped
    void requestViewChange(ViewType requestedView);

protected:
    void showEvent(QShowEvent *event) override;

private:
    KitchenController *controller;   // Figure 1: OrderQueueView -> KitchenController
    OrderDetailsView *detailsDialog;   // Figure 1: OrderQueueView -> OrderDetailsView

    Ui::OrderQueueView *ui;

private slots:
    void dashboardBtnClicked();
    void orderDetailsBtnClicked(int orderId);

};

#endif // ORDERQUEUEVIEW_H
