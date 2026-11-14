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

namespace {

const char *const DATE_FORMAT = "yyyy-MM-dd:HH:mm";
const char *const STATUS_COMPLETED = "Completed";

Customer *findCustomer(CafeDataStore &store, const QString &username)
{
    return dynamic_cast<Customer *>(store.findUser(username));
}

QString customerName(CafeDataStore &store, const Order &order)
{
    const Customer *customer = findCustomer(store, order.customerUsername());
    return customer ? customer->name() : QString();
}

Order *findQueuedOrder(CafeDataStore &store, int orderId)
{
    const QVector<Order *> orders = store.orderQueue().orders();
    for (Order *order : orders) {
        if (order->orderId() == orderId)
            return order;
    }
    return nullptr;
}

KitchenItem toKitchenItem(const OrderItem &line)
{
    const MenuItem *menuItem = line.menuItem();

    KitchenItem item;
    item.name = menuItem->name();
    item.quantity = line.quantity();

    const QVector<RecipeIngredient> recipe = menuItem->ingredients();
    for (const RecipeIngredient &part : recipe)
        item.ingredients.append(QString("%1 %2").arg(part.quantity()).arg(part.ingredient()->name()));
    return item;
}

}

KitchenController::KitchenController()
    : store(CafeDataStore::instance())
{
}

QList<QueueEntry> KitchenController::queue() const
{
    const QVector<Order *> orders = store.orderQueue().orders();

    QList<QueueEntry> result;
    for (const Order *order : orders) {
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
        return {};

    KitchenOrderDetails result;
    result.isValid = true;
    result.orderId = order->orderId();
    result.customerName = customerName(store, *order);
    result.placedAt = order->placedAt().toString(DATE_FORMAT);
    result.status = order->status();

    const QVector<OrderItem> lines = order->items();
    for (const OrderItem &line : lines)
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
