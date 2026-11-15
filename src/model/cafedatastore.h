#ifndef CAFEDATASTORE_H
#define CAFEDATASTORE_H
#include  <QString>
#include <QList>
#include <memory>
#include "order.h"

class DataStorage;
class User;
class MenuItem;
class OrderQueue;

class CafeDataStore
{
public:
    static CafeDataStore &instance();
    CafeDataStore(const CafeDataStore &) = delete;
    CafeDataStore &operator=(const CafeDataStore &) = delete;

    User* findUser(const QString &nameOrUsername);
    QList<MenuItem*> menuItems() const;
    OrderQueue& orderQueue();
    Order* addOrder(std::unique_ptr<Order> order);
    int nextOrderId() const;

private:
    CafeDataStore();
    ~CafeDataStore();
    DataStorage *storage;

};

#endif // CAFEDATASTORE_H
