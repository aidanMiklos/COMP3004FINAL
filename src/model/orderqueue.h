#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H
#include "order.h"
#include <QVector>

class OrderQueue
{
public:
    void addOrder(Order *order);
    QVector<Order*> orders()const;
    bool removeOrder(int orderId);
    int size() const;

private:
    QVector<Order*> m_orders;
};

#endif // ORDERQUEUE_H
