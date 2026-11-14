/*
 * DashboardController -- Controller subsystem (control class)
 *
 * Supplies the customer dashboard: account details, current order and order
 * history.
 *
 * Spec notes:
 *   - The current order is shown while In Progress or Completed. [D1 p.3
 *     Feature 4]
 *   - The history is the last 5 orders that reached Picked Up or Cancelled.
 *     [Overview sec. 2, Online Dashboard]
 *   - Optional: update email and home address. [Overview sec. 2, Online
 *     Dashboard]
 */

#ifndef DASHBOARDCONTROLLER_H
#define DASHBOARDCONTROLLER_H

#include <QList>
#include <QString>
#include <QStringList>

class CafeDataStore;

struct CustomerDetails
{
    QString name;
    QString loyaltyNumber;
    QString email;
    QString homeAddress;
    int loyaltyPoints = 0;
    int creditCents = 0;
};

struct OrderSummary
{
    int orderId = 0;
    QString placedAt;
    QString orderType;
    QString status;
    QStringList items;
    int totalCents = 0;
    int amountChargedCents = 0;
    int pointsUsed = 0;
    int pointsEarned = 0;
    int creditUsedCents = 0;
};

class DashboardController
{
public:
    DashboardController();

    // Done: operations for the views. Pass the logged-in username in
    //       (MainWindow gets it from AccountController) and return plain
    //       data (QString, numbers), not model pointers.

    CustomerDetails details(const QString &username) const;
    bool hasCurrentOrder(const QString &username) const;
    OrderSummary currentOrder(const QString &username) const;
    QList<OrderSummary> orderHistory(const QString &username) const;
    bool updateContact(const QString &username, const QString &email,
                       const QString &homeAddress);

private:
    CafeDataStore &store;
};

#endif // DASHBOARDCONTROLLER_H
