#include "customer.h"

Customer::Customer(const QString &name, const QString &username, const QString &email, int loyaltyPoints)
    :User(name,username),m_email(email), m_loyaltyPoints(loyaltyPoints),m_creditCents(0)
{

}
QString Customer::roleName() const{
    return "Customer";
}

QString Customer::email() const{
    return m_email;
}

int Customer::loyaltyPoints() const{
    return m_loyaltyPoints;
}
void Customer::addLoyaltyPoints(int points){
    if (points > 0){
        m_loyaltyPoints += points;
    }
}

bool Customer::useLoyaltyPoints(int points){
        if (points < 0 || points > m_loyaltyPoints){
            return false;
        }
        m_loyaltyPoints -= points;
        return true;
    }

int Customer::creditCents()const{
    return m_creditCents;
}

void Customer::setCreditCents(int credit){
    if(credit >= 0){
        m_creditCents = credit;
    }
}

void Customer::addOrder(const Order &order){
    m_orderHistory.append(order);
}

QVector<Order> Customer::orderHistory()const{
    return m_orderHistory;
}

QString Customer::loyaltyNumber() const{
    return m_loyaltyNumber;
}

QString Customer::homeAddress() const{
    return m_homeAddress;
}

void Customer::setLoyaltyNumber(const QString &number){
    m_loyaltyNumber = number;
}

void Customer::setHomeAddress(const QString &address){
    m_homeAddress = address;
}
