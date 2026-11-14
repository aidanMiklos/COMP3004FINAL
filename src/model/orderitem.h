#ifndef ORDERITEM_H
#define ORDERITEM_H
#include "menuitem.h"

class OrderItem
{
public:
    OrderItem(MenuItem *menuItem, int quantity);
    MenuItem* menuItem()const;
    int quantity()const;
    int subtotalCents() const;
    void setQuantity(int quantity);

private:
    MenuItem *m_menuItem;
    int m_quantity;
};

#endif // ORDERITEM_H
