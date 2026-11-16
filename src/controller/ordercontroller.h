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

#include <memory>

#include <QString>

class AccountController;
class CafeDataStore;
class Customer;
class Order;

struct PriceBreakdown
{
    bool isValid = false;
    int subtotalCents = 0;
    int taxCents = 0;
    int totalCents = 0;
    int pointsUsed = 0;
    int creditUsedCents = 0;
    int amountChargedCents = 0;
};

class OrderController
{
public:
    // Exact message the D1 outline requires (p.3, Business Rules).
    static constexpr const char *ONE_ORDER_MESSAGE = "Only one order can be placed at a time";

    explicit OrderController(AccountController &accounts);
    ~OrderController();

    bool canPlaceOrder() const;
    int availablePoints() const;
    int availableCreditCents() const;
    int maxPointsAllowed() const;
    int maxCreditAllowedCents(int points) const;
    bool startOrder();
    bool addItem(const QString &menuItemName, int quantity);
    void cancelOrder();
    PriceBreakdown breakdown(int points, int creditCents) const;
    bool submitOrder(int points, int creditCents);

private:
    Customer *currentCustomer() const;
    bool ownsDraft() const;

    CafeDataStore &store;
    AccountController &accounts;
    std::unique_ptr<Order> draftOrder;
    QString draftUsername;
};

#endif // ORDERCONTROLLER_H
