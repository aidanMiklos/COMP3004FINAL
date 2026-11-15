/*
 * OrderDetailsView -- View subsystem (boundary class)
 *
 * Dialog showing one order for the kitchen, with a Mark Completed button.
 *
 * Spec notes:
 *   - Kitchen staff can view an order's details and the items and their
 *     ingredients to prepare. [Overview sec. 2, Staff: Kitchen; D1 p.3
 *     Feature 6]
 *   - When the order is prepared, kitchen staff change its status from In
 *     Progress to Completed. [Overview sec. 2, Staff: Kitchen; D1 p.3
 *     Feature 7]
 */

#ifndef ORDERDETAILSVIEW_H
#define ORDERDETAILSVIEW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class OrderDetailsView; }
QT_END_NAMESPACE

class KitchenController;

class OrderDetailsView : public QDialog
{
    Q_OBJECT

public:
    explicit OrderDetailsView(KitchenController *controller, QWidget *parent = nullptr);

    void requestedOrderId(int orderId);

signals:

    void signalOrderSetCompleted();

private:
    KitchenController *controller;   // Figure 1: OrderDetailsView -> KitchenController
    int orderId;    // Used to store a given order's ID with the OrderDetailView. Prevents having to disconnect and reconnect the complete button

    Ui::OrderDetailsView *ui;

private slots:
    void completeBtnClicked();

};

#endif // ORDERDETAILSVIEW_H
