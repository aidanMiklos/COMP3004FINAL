#ifndef ORDER_H
#define ORDER_H
#include <QVector>
#include <QString>
#include "orderitem.h"
#include <QDateTime>

class Order
{
public:
    Order(int orderId);
    int orderId()const;
    void addItem(const OrderItem &item);
    QVector<OrderItem> items()const;
    int subtotalCents()const;
    int taxCents()const;
    int totalCents() const;
    int pointsUsed() const;
    int creditUsedCents()const;
    int amountChargedCents() const;
    QString status()const;
    void setStatus(const QString &status);
    QString orderType()const;
    void setOrderType(const QString &type);
    int pointsEarned() const;
    void setPayment(int points, int creditCents, int chargedCents, int earned);
    QDateTime placedAt()const;
    void setPlacedAt(const QDateTime &dateTime);
    QString customerUsername()const;
    void setCustomerUsername(const QString &username);
    bool calculatePayment(int points, int creditCents);
private:
    int m_orderId;
    QVector<OrderItem> m_items;
    QString m_status;
    QString m_orderType;
    int m_pointsUsed;
    int m_creditUsedCents;
    int m_amountChargedCents;
    int m_pointsEarned;
    QDateTime m_placedAt;
    QString m_customerUsername;
};

#endif // ORDER_H
