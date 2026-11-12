#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "User.h"
#include <QString>

class Customer : public User
{
public:
    Customer(int id, const QString &name, const QString &email, int loyaltyPoints);
    QString getRole() const override;
    QString getEmail() const;
    int getLoyaltyPoints() const;
    void addLoyaltyPoints(int points);
    bool useLoyaltyPoints(int points);

private:
        QString email;
        int loyaltyPoints;
};

#endif // CUSTOMER_H
