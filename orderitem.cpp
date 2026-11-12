#include "orderitem.h"

OrderItem::OrderItem(MenuItem *menuItem, int quantity): m_menuItem(menuItem),
    m_quantity(quantity > 0 ? quantity: 1)
{
}

MenuItem* OrderItem::menuItem()const{
    return m_menuItem;
}

int OrderItem::quantity()const{
    return m_quantity;
}

int OrderItem::subtotalCents() const{
    if(m_menuItem ==nullptr){
        return 0;
    }
    return m_menuItem->priceCents()*m_quantity;
}

void OrderItem::setQuantity(int quantity){
    if(quantity >0){
        m_quantity = quantity;
    }
}
