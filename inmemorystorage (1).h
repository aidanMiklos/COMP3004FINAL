#ifndef INMEMORYSTORAGE_H
#define INMEMORYSTORAGE_H
#include <QList>
#include"datastorage.h"

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

private:
    QList <User*> users;
    QList<MenuItem*> menu;
    QList<Ingredient*> ingredients;
    OrderQueue *kitchenQueue;
};

#endif // INMEMORYSTORAGE_H
