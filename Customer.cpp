#include "Customer.h"

Customer::Customer(int id, const QString &name, const QString &email, int loyaltyPoints)
    :User(id, name),email(email), loyaltyPoints(loyaltyPoints)
{
}

QString Customer::getRole() const{
    return "Customer";
}

QString Customer::getEmail() const{
    return email;
}

int Customer::getLoyaltyPoints() const{
    return loyaltyPoints;
}
void Customer::addLoyaltyPoints(int points){
    if (points > 0){
        loyaltyPoints += points;
    }
}
bool Customer::useLoyaltyPoints(int points){
        if (points < 0 || points > loyaltyPoints){
            return false;
        }
        loyaltyPoints -= points;
        return true;
    }
