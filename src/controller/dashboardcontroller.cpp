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

const int HISTORY_LIMIT = 5;
const QString DATE_FORMAT = "yyyy-MM-dd:HH:mm";

static Customer *findCustomer(CafeDataStore &store, const QString &username)
{
    return dynamic_cast<Customer *>(store.findUser(username));
}

static bool isFinished(const Order &order)
{
    return order.status() == "Picked Up" || order.status() == "Cancelled";
}

static QStringList itemLines(const Order &order)
{
    QStringList lines;
    for (const OrderItem &item : order.items())
        lines.append(QString::number(item.quantity()) + " x " + item.menuItem()->name());
    return lines;
}

static OrderSummary summarize(const Order &order)
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

DashboardController::DashboardController()
    : store(CafeDataStore::instance())
{
}

CustomerDetails DashboardController::details(const QString &username) const
{
    const Customer *customer = findCustomer(store, username);
    if (!customer)
        return CustomerDetails();

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
    if (!customer)
        return false;

    for (const Order &order : customer->orderHistory()) {
        if (!isFinished(order))
            return true;
    }
    return false;
}

OrderSummary DashboardController::currentOrder(const QString &username) const
{
    const Customer *customer = findCustomer(store, username);
    if (!customer)
        return OrderSummary();

    for (const Order &order : customer->orderHistory()) {
        if (!isFinished(order))
            return summarize(order);
    }
    return OrderSummary();
}

QList<OrderSummary> DashboardController::orderHistory(const QString &username) const
{
    const Customer *customer = findCustomer(store, username);
    if (!customer)
        return QList<OrderSummary>();

    const QVector<Order> orders = customer->orderHistory();

    QList<OrderSummary> result;
    for (int i = orders.size() - 1; i >= 0; i--) {
        if (result.size() == HISTORY_LIMIT)
            break;
        if (isFinished(orders[i]))
            result.append(summarize(orders[i]));
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
