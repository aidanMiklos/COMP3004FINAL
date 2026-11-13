#include "inmemorystorage.h"
#include "ingredient.h"
#include "menuitem.h"
#include "orderqueue.h"
#include "user.h"
#include <QtAlgorithms>

InMemoryStorage::InMemoryStorage():kitchenQueue(new OrderQueue)
{
}

InMemoryStorage::~InMemoryStorage(){
    delete kitchenQueue;
    qDeleteAll(users);
    qDeleteAll(menu);
    qDeleteAll(ingredients);
}

User* InMemoryStorage::findUser(const QString &nameOrUsername){
    for (User *user : users){
        if(user->username()==nameOrUsername
           || user->name() == nameOrUsername){
                return user;
            }
    }
    return nullptr;
}

void InMemoryStorage::addUser(User *user){
    if(user != nullptr && !users.contains(user)){
        users.append(user);
    }
}

QList<MenuItem*> InMemoryStorage::menuItems() const{
    return menu;
}

void InMemoryStorage::addMenuItem(MenuItem *item){
    if (item != nullptr && !menu.contains(item)){
        menu.append(item);
    }
}

void InMemoryStorage::addIngredient(Ingredient *ingredient){
    if (ingredient != nullptr && !ingredients.contains(ingredient)){
        ingredients.append(ingredient);
    }
}

OrderQueue& InMemoryStorage::orderQueue(){
    return *kitchenQueue;
}

Order* InMemoryStorage::addOrder(std::unique_ptr<Order> order){
    if(!order)
        return nullptr;
    for(const auto &existing : storedOrders){
        if (existing->orderId() == order->orderId())
                return nullptr;
    }
    Order *result = order.get();
    storedOrders.push_back(std::move(order));
    return result;
}

Order* InMemoryStorage::findOrder(int orderId){
    for (const auto &order : storedOrders){
        if(order->orderId() == orderId)
            return order.get();
    }
    return nullptr;
}
