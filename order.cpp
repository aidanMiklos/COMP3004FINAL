#include "order.h"

Order::Order(int orderId):
    m_orderId(orderId), m_status("Pending"), m_orderType("Online"),
    m_pointsUsed(0), m_creditUsedCents(0), m_amountChargedCents(0), m_pointsEarned(0),
    m_placedAt(QDateTime::currentDateTime())
{
}

int Order::orderId() const{
    return m_orderId;
}

void Order::addItem(const OrderItem &item){
    m_items.append(item);
}

QVector<OrderItem> Order::items()const{
    return m_items;
}

int Order::subtotalCents() const{
    int subtotal =0;
    for(const OrderItem &item : m_items){
        subtotal += item.subtotalCents();
    }
    return subtotal;
}

int Order::taxCents()const{
    return(subtotalCents()*15 + 50)/100;
}

int Order::totalCents()const{
    return subtotalCents()+ taxCents();
}

QString Order::status() const{
    return m_status;
}

void Order::setStatus(const QString &status){
    m_status = status;
}

QString Order::orderType() const{
    return m_orderType;
}

void Order::setOrderType(const QString &type){
    m_orderType = type;
}
int Order::pointsUsed() const{
    return m_pointsUsed;
}

int Order::creditUsedCents()const{
    return m_creditUsedCents;
}
int Order::amountChargedCents() const{
    return m_amountChargedCents;
}
int Order::pointsEarned()const{
    return m_pointsEarned;
}
void Order::setPayment(int points, int creditCents, int chargedCents, int earned){
    m_pointsUsed = points;
    m_creditUsedCents = creditCents;
    m_amountChargedCents = chargedCents;
    m_pointsEarned = earned;
}

QDateTime Order::placedAt() const{
    return m_placedAt;
}
void Order::setPlacedAt(const QDateTime &dateTime){
    m_placedAt = dateTime;
}

bool Order::calculatePayment(int points, int creditCents){
    int maxPoints = (subtotalCents() / 2) / 100;
    int pointsValue = points * 100;

    if (points < 0 || points > maxPoints || creditCents < 0)
        return false;

    int remaining = totalCents() - pointsValue;
    if (creditCents > remaining)
        return false;
    m_pointsUsed = points;
    m_creditUsedCents = creditCents;
    m_amountChargedCents = remaining - creditCents;
    m_pointsEarned = 0;
    return true;
}
