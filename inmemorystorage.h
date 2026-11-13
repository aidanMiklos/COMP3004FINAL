#ifndef INMEMORYSTORAGE_H
#define INMEMORYSTORAGE_H
#include <QList>
#include"datastorage.h"
#include <memory>
#include <vector>
#include "order.h"

class Ingredient;
class MenuItem;
class OrderQueue;
class User;

class InMemoryStorage: public DataStorage
{
public:
    InMemoryStorage();
    ~InMemoryStorage() override;

    InMemoryStorage(const InMemoryStorage &) = delete;
    InMemoryStorage &operator=(const InMemoryStorage &) = delete;

    User* findUser(const QString &nameOrUsername) override;
    void addUser(User *user) override;

    QList<MenuItem*> menuItems() const override;
    void addMenuItem(MenuItem *item) override;

    void addIngredient(Ingredient *ingredient) override;
    OrderQueue& orderQueue() override;

    Order *addOrder(std::unique_ptr<Order> order)override;
    Order *findOrder(int orderId);
private:
    QList <User*> users;
    QList<MenuItem*> menu;
    QList<Ingredient*> ingredients;
    OrderQueue *kitchenQueue;
    std::vector<std::unique_ptr<Order>> storedOrders;

};

#endif // INMEMORYSTORAGE_H
