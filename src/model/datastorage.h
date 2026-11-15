#ifndef DATASTORAGE_H
#define DATASTORAGE_H
#include <QString>
#include <QList>
#include <memory>
#include "order.h"
class User;
class MenuItem;
class Ingredient;
class OrderQueue;


class DataStorage
{
public:
    virtual ~DataStorage() = default;

    virtual User* findUser(const QString &nameOrUsername) = 0;
    virtual void addUser(User *user) = 0;

    virtual QList<MenuItem*> menuItems()const =0;
    virtual void addMenuItem(MenuItem *item)= 0;

    virtual void addIngredient(Ingredient *ingredient) = 0;

    virtual OrderQueue& orderQueue()=0;

    virtual Order* addOrder(std::unique_ptr<Order> order) = 0;
    virtual int nextOrderId() const = 0;

};

#endif // DATASTORAGE_H
