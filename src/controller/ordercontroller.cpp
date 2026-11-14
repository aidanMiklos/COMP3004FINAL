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

#include "cafedatastore.h"
#include "customer.h"
#include "menuitem.h"
#include "order.h"
#include "orderitem.h"
#include "orderqueue.h"

namespace {

const char *const STATUS_IN_PROGRESS = "In Progress";
const char *const STATUS_PICKED_UP = "Picked Up";
const char *const STATUS_CANCELLED = "Cancelled";
const char *const TYPE_ONLINE = "Online";

Customer *findCustomer(CafeDataStore &store, const QString &username)
{
    return dynamic_cast<Customer *>(store.findUser(username));
}

bool hasOpenOrder(const Customer &customer)
{
    const QVector<Order> orders = customer.orderHistory();
    for (const Order &order : orders) {
        if (order.status() != STATUS_PICKED_UP && order.status() != STATUS_CANCELLED)
            return true;
    }
    return false;
}

}

OrderController::OrderController()
    : store(CafeDataStore::instance())
{
}

OrderController::~OrderController() = default;

bool OrderController::canPlaceOrder(const QString &username) const
{
    const Customer *customer = findCustomer(store, username);
    return customer && !hasOpenOrder(*customer);
}

bool OrderController::startOrder(const QString &username)
{
    if (!canPlaceOrder(username))
        return false;

    draftOrder = std::make_unique<Order>(store.nextOrderId());
    draftUsername = username;
    return true;
}

bool OrderController::addItem(const QString &menuItemName, int quantity)
{
    if (!draftOrder || quantity <= 0)
        return false;

    const QList<MenuItem *> items = store.menuItems();
    for (MenuItem *item : items) {
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

PriceBreakdown OrderController::breakdown(const QString &username, int points,
                                          int creditCents) const
{
    const Customer *customer = findCustomer(store, username);
    if (!customer || !ownsDraft(username))
        return {};

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

bool OrderController::submitOrder(const QString &username, int points, int creditCents)
{
    Customer *customer = findCustomer(store, username);
    if (!customer || !ownsDraft(username) || draftOrder->items().isEmpty() || hasOpenOrder(*customer))
        return false;

    if (!customer->payForOrder(*draftOrder, points, creditCents))
        return false;

    draftOrder->setStatus(STATUS_IN_PROGRESS);
    draftOrder->setOrderType(TYPE_ONLINE);
    draftOrder->setPlacedAt(QDateTime::currentDateTime());
    draftOrder->setCustomerUsername(username);

    Order *placed = store.addOrder(std::move(draftOrder));
    draftUsername.clear();
    if (!placed)
        return false;

    store.orderQueue().addOrder(placed);
    customer->placeOrder(*placed);
    return true;
}

bool OrderController::ownsDraft(const QString &username) const
{
    return draftOrder && draftUsername == username;
}
