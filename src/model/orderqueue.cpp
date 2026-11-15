#include "orderqueue.h"

void OrderQueue::addOrder(Order *order)
{
    if(order != nullptr){
        m_orders.append(order);
    }
}

QVector<Order*> OrderQueue::orders()const{
    return m_orders;
}

bool OrderQueue::removeOrder(int orderId)
{
    for (int i=0; i<m_orders.size();i++){
        if(m_orders[i]->orderId() == orderId){
            m_orders.removeAt(i);
            return true;
        }
    }
    return false;
}

int OrderQueue::size() const{
    return m_orders.size();
}
