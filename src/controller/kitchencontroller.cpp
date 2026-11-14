/*
 * KitchenController -- implementation
 *
 * TODO:
 *   - Complete: tell the Order it is completed (which credits the customer's
 *     earned points), then remove it from the OrderQueue. [Overview sec. 3;
 *     D1 p.3 Feature 7]
 */

#include "kitchencontroller.h"

#include <QDateTime>
#include <QVector>

#include "cafedatastore.h"
#include "customer.h"
#include "ingredient.h"
#include "menuitem.h"
#include "order.h"
#include "orderitem.h"
#include "orderqueue.h"
#include "recipeingredient.h"

const QString DATE_FORMAT = "yyyy-MM-dd:HH:mm";
const QString STATUS_COMPLETED = "Completed";

static Customer *findCustomer(CafeDataStore &store, const QString &username)
{
    return dynamic_cast<Customer *>(store.findUser(username));
}

static QString customerName(CafeDataStore &store, const Order &order)
{
    const Customer *customer = findCustomer(store, order.customerUsername());
    if (!customer)
        return QString();
    return customer->name();
}

static Order *findQueuedOrder(CafeDataStore &store, int orderId)
{
    for (Order *order : store.orderQueue().orders()) {
        if (order->orderId() == orderId)
            return order;
    }
    return nullptr;
}

static KitchenItem toKitchenItem(const OrderItem &line)
{
    const MenuItem *menuItem = line.menuItem();

    KitchenItem item;
    item.name = menuItem->name();
    item.quantity = line.quantity();

    for (const RecipeIngredient &part : menuItem->ingredients())
        item.ingredients.append(QString::number(part.quantity()) + " " + part.ingredient()->name());
    return item;
}

KitchenController::KitchenController()
    : store(CafeDataStore::instance())
{
}

QList<QueueEntry> KitchenController::queue() const
{
    QList<QueueEntry> result;
    for (const Order *order : store.orderQueue().orders()) {
        QueueEntry entry;
        entry.orderId = order->orderId();
        entry.customerName = customerName(store, *order);
        entry.placedAt = order->placedAt().toString(DATE_FORMAT);
        result.append(entry);
    }
    return result;
}

KitchenOrderDetails KitchenController::orderDetails(int orderId) const
{
    const Order *order = findQueuedOrder(store, orderId);
    if (!order)
        return KitchenOrderDetails();

    KitchenOrderDetails result;
    result.isValid = true;
    result.orderId = order->orderId();
    result.customerName = customerName(store, *order);
    result.placedAt = order->placedAt().toString(DATE_FORMAT);
    result.status = order->status();

    for (const OrderItem &line : order->items())
        result.items.append(toKitchenItem(line));
    return result;
}

bool KitchenController::completeOrder(int orderId)
{
    Order *order = findQueuedOrder(store, orderId);
    if (!order)
        return false;

    order->setStatus(STATUS_COMPLETED);

    Customer *customer = findCustomer(store, order->customerUsername());
    if (customer) {
        customer->updateOrderStatus(orderId, STATUS_COMPLETED);
        customer->earnPoints(order->pointsEarned());
    }

    return store.orderQueue().removeOrder(orderId);
}
