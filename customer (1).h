#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "user.h"
#include "order.h"
#include <QString>
#include <QVector>

class Customer : public User
{
public:
    Customer(const QString &name, const QString &username, const QString &email, int loyaltyPoints);
    QString roleName() const override;
    QString email() const;
    int loyaltyPoints() const;
    void addLoyaltyPoints(int points);
    bool useLoyaltyPoints(int points);
    int creditCents() const;
    void setCreditCents(int credit);
    void addOrder(const Order &order);
    QVector<Order> orderHistory() const;

    QString loyaltyNumber() const;
    QString homeAddress() const;
    void setLoyaltyNumber(const QString &number);
    void setHomeAddress(const QString &address);


private:
        QString m_email;
        int m_loyaltyPoints;
        int m_creditCents;
        QVector<Order> m_orderHistory;
        QString m_loyaltyNumber;
        QString m_homeAddress;
};

#endif // CUSTOMER_H
