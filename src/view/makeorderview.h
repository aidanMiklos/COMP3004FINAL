/*
 * MakeOrderView -- View subsystem (boundary class)
 *
 * The customer's ordering page: pick items from the embedded MenuView,
 * choose loyalty points and account credit, see the price breakdown update
 * live, then submit through OrderController.
 *
 * Spec notes:
 *   - Before the order is submitted, show the subtotal, tax, final price
 *     with tax, loyalty points redeemed, account credit applied, and the
 *     amount to be paid. [D1 p.3 Feature 3]
 *   - The customer can apply loyalty points or account credit to the order.
 *     [Overview sec. 2, Ordering Application]
 *   - If the customer already has a current order, block the new one and
 *     show OrderController::ONE_ORDER_MESSAGE. [D1 p.3-4 Business Rules]
 */

#ifndef MAKEORDERVIEW_H
#define MAKEORDERVIEW_H

#include <QWidget>

class OrderController;
class MenuController;
class MenuView;

class MakeOrderView : public QWidget
{
    Q_OBJECT

public:
    explicit MakeOrderView(OrderController *controller, MenuController *menuController, QWidget *parent = nullptr);

private:
    OrderController *controller;   // Figure 1: MakeOrderView -> OrderController
    MenuView *menuView;       // Figure 1: MakeOrderView -> MenuView (embedded)
};

#endif // MAKEORDERVIEW_H
