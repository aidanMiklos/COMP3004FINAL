/*
 * OrderController -- implementation
 *
 * TODO:
 *   - Before starting or submitting, check whether the customer already has
 *     a current order. [D1 p.3-4 Business Rules]
 *   - Submit: take points and credit from the Customer, set the amount
 *     charged, mark it paid, set In Progress and the date/time, add it to
 *     the OrderQueue, and make it the customer's current order. [D1 p.3-4
 *     Business Rules; Overview sec. 3]
 *   - The pricing maths lives in Order (see order.cpp), not here.
 */

#include "ordercontroller.h"

#include <QDateTime>
#include <QList>
#include <QVector>

#include "accountcontroller.h"
#include "cafedatastore.h"
#include "customer.h"
#include "menuitem.h"
#include "order.h"
#include "orderitem.h"
#include "orderqueue.h"

const QString STATUS_IN_PROGRESS = "In Progress";
const QString STATUS_PICKED_UP = "Picked Up";
const QString STATUS_CANCELLED = "Cancelled";
const QString TYPE_ONLINE = "Online";

static bool hasOpenOrder(const Customer &customer)
{
    for (const Order &order : customer.orderHistory()) {
        if (order.status() != STATUS_PICKED_UP && order.status() != STATUS_CANCELLED)
            return true;
    }
    return false;
}

OrderController::OrderController(AccountController &accounts)
    : store(CafeDataStore::instance()), accounts(accounts)
{
}

OrderController::~OrderController()
{
}

bool OrderController::canPlaceOrder() const
{
    const Customer *customer = currentCustomer();
    return customer && !hasOpenOrder(*customer);
}

int OrderController::availablePoints() const
{
    const Customer *customer = currentCustomer();
    return customer ? customer->loyaltyPoints() : 0;
}

int OrderController::availableCreditCents() const
{
    const Customer *customer = currentCustomer();
    return customer ? customer->creditCents() : 0;
}

bool OrderController::startOrder()
{
    if (!canPlaceOrder())
        return false;

    draftOrder = std::make_unique<Order>(store.nextOrderId());
    draftUsername = accounts.currentUsername();
    return true;
}

bool OrderController::addItem(const QString &menuItemName, int quantity)
{
    if (!draftOrder || quantity <= 0)
        return false;

    for (MenuItem *item : store.menuItems()) {
        if (item->name() == menuItemName) {
            draftOrder->addItem(OrderItem(item, quantity));
            return true;
        }
    }
    return false;
}

void OrderController::cancelOrder()
{
    draftOrder.reset();
    draftUsername.clear();
}

PriceBreakdown OrderController::breakdown(int points, int creditCents) const
{
    const Customer *customer = currentCustomer();
    if (!customer || !ownsDraft())
        return PriceBreakdown();

    Order preview = *draftOrder;

    PriceBreakdown result;
    result.subtotalCents = preview.subtotalCents();
    result.taxCents = preview.taxCents();
    result.totalCents = preview.totalCents();

    const bool canAfford = points <= customer->loyaltyPoints()
                           && creditCents <= customer->creditCents();
    if (!canAfford || !preview.calculatePayment(points, creditCents))
        return result;

    result.isValid = true;
    result.pointsUsed = preview.pointsUsed();
    result.creditUsedCents = preview.creditUsedCents();
    result.amountChargedCents = preview.amountChargedCents();
    return result;
}

bool OrderController::submitOrder(int points, int creditCents)
{
    Customer *customer = currentCustomer();
    if (!customer || !ownsDraft() || draftOrder->items().isEmpty() || hasOpenOrder(*customer))
        return false;

    if (!customer->payForOrder(*draftOrder, points, creditCents))
        return false;

    draftOrder->setStatus(STATUS_IN_PROGRESS);
    draftOrder->setOrderType(TYPE_ONLINE);
    draftOrder->setPlacedAt(QDateTime::currentDateTime());
    draftOrder->setCustomerUsername(draftUsername);

    Order *placed = store.addOrder(std::move(draftOrder));
    draftUsername.clear();
    if (!placed)
        return false;

    store.orderQueue().addOrder(placed);
    customer->placeOrder(*placed);
    return true;
}

Customer *OrderController::currentCustomer() const
{
    if (!accounts.isLoggedIn())
        return nullptr;
    return dynamic_cast<Customer *>(store.findUser(accounts.currentUsername()));
}

bool OrderController::ownsDraft() const
{
    return draftOrder && draftUsername == accounts.currentUsername();
}
