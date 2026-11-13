/*
 * DashboardController -- implementation
 *
 * TODO:
 *   - Look up the logged-in customer through CafeDataStore and return
 *     display data. [D1 p.3 Feature 4]
 */

#include "dashboardcontroller.h"

#include <QDateTime>
#include <QVector>

#include "cafedatastore.h"
#include "customer.h"
#include "menuitem.h"
#include "order.h"
#include "orderitem.h"

namespace {

const int HISTORY_LIMIT = 5;
const char *const DATE_FORMAT = "yyyy-MM-dd:HH:mm";

Customer *findCustomer(CafeDataStore &store, const QString &username)
{
    return dynamic_cast<Customer *>(store.findUser(username));
}

bool isFinished(const Order &order)
{
    return order.status() == "Picked Up" || order.status() == "Cancelled";
}

int currentOrderIndex(const QVector<Order> &orders)
{
    for (int i = orders.size() - 1; i >= 0; --i) {
        if (!isFinished(orders.at(i)))
            return i;
    }
    return -1;
}

QStringList itemLines(const Order &order)
{
    const QVector<OrderItem> items = order.items();

    QStringList lines;
    for (const OrderItem &item : items)
        lines.append(QString("%1 x %2").arg(item.quantity()).arg(item.menuItem()->name()));
    return lines;
}

OrderSummary summarize(const Order &order)
{
    OrderSummary summary;
    summary.orderId = order.orderId();
    summary.placedAt = order.placedAt().toString(DATE_FORMAT);
    summary.orderType = order.orderType();
    summary.status = order.status();
    summary.items = itemLines(order);
    summary.totalCents = order.totalCents();
    summary.amountChargedCents = order.amountChargedCents();
    summary.pointsUsed = order.pointsUsed();
    summary.pointsEarned = order.pointsEarned();
    summary.creditUsedCents = order.creditUsedCents();
    return summary;
}

}

DashboardController::DashboardController()
    : store(CafeDataStore::instance())
{
}

CustomerDetails DashboardController::details(const QString &username) const
{
    const Customer *customer = findCustomer(store, username);
    if (!customer)
        return {};

    CustomerDetails result;
    result.name = customer->name();
    result.loyaltyNumber = customer->loyaltyNumber();
    result.email = customer->email();
    result.homeAddress = customer->homeAddress();
    result.loyaltyPoints = customer->loyaltyPoints();
    result.creditCents = customer->creditCents();
    return result;
}

bool DashboardController::hasCurrentOrder(const QString &username) const
{
    const Customer *customer = findCustomer(store, username);
    return customer && currentOrderIndex(customer->orderHistory()) >= 0;
}

OrderSummary DashboardController::currentOrder(const QString &username) const
{
    const Customer *customer = findCustomer(store, username);
    if (!customer)
        return {};

    const QVector<Order> orders = customer->orderHistory();
    const int index = currentOrderIndex(orders);
    if (index < 0)
        return {};

    return summarize(orders.at(index));
}

QList<OrderSummary> DashboardController::orderHistory(const QString &username) const
{
    const Customer *customer = findCustomer(store, username);
    if (!customer)
        return {};

    const QVector<Order> orders = customer->orderHistory();

    QList<OrderSummary> result;
    for (int i = orders.size() - 1; i >= 0 && result.size() < HISTORY_LIMIT; --i) {
        if (isFinished(orders.at(i)))
            result.append(summarize(orders.at(i)));
    }
    return result;
}

bool DashboardController::updateContact(const QString &username, const QString &email,
                                        const QString &homeAddress)
{
    Customer *customer = findCustomer(store, username);
    const QString newEmail = email.trimmed();
    const QString newAddress = homeAddress.trimmed();

    if (!customer || newEmail.isEmpty() || !newEmail.contains('@') || newAddress.isEmpty())
        return false;

    customer->setEmail(newEmail);
    customer->setHomeAddress(newAddress);
    return true;
}
