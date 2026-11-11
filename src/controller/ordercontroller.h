/*
 * OrderController -- Controller subsystem (control class)
 *
 * Builds the customer's draft order, provides the price breakdown, enforces
 * the one-order rule and submits the order. Holds the draft (Figure 1:
 * OrderController -> Order).
 *
 * Spec notes:
 *   - A customer may have only one current order; if one exists, block
 *     placing another and show ONE_ORDER_MESSAGE (exact wording required).
 *     [D1 p.3-4 Business Rules]
 *   - Orders are recorded as paid, and the amount charged is what is left
 *     after loyalty points and account credit. No payment system is called.
 *     [D1 p.3-4 Business Rules]
 *   - A paid order enters the kitchen queue with status In Progress.
 *     [Overview sec. 2, Order Queue Process; Overview sec. 3]
 *   - Tax is calculated on the full subtotal before points or credit are
 *     applied. [D1 p.3 Feature 3]
 */

#ifndef ORDERCONTROLLER_H
#define ORDERCONTROLLER_H

class CafeDataStore;
class Order;

class OrderController
{
public:
    // Exact message the D1 outline requires (p.3, Business Rules).
    static constexpr const char *ONE_ORDER_MESSAGE = "Only one order can be placed at a time";

    OrderController();
    ~OrderController();

    // TODO: operations for the views. Pass the logged-in username in
    //       (MainWindow gets it from AccountController) and return plain
    //       data (QString, numbers), not model pointers.

private:
    CafeDataStore &store;   // Figure 1: OrderController -> CafeDataStore
    Order *draftOrder = nullptr;   // Figure 1: OrderController -> Order (order being built)
};

#endif // ORDERCONTROLLER_H
