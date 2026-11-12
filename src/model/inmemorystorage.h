/*
 * InMemoryStorage -- Model subsystem (Bridge implementation)
 *
 * The D1 implementation of DataStorage: keeps every user, menu item,
 * ingredient and the order queue in memory, and owns them.
 *
 * Spec notes:
 *   - Data objects are stored in memory. [D1 p.2 Default System Data]
 *   - On restart the kitchen queue is empty, the last run's orders are gone,
 *     and histories and balances are back to their defaults. This happens
 *     automatically: memory starts empty and DefaultDataLoader refills it.
 *     [D1 p.2 Restart rules]
 */

#ifndef INMEMORYSTORAGE_H
#define INMEMORYSTORAGE_H

#include <QList>

#include "datastorage.h"

class Ingredient;
class MenuItem;
class OrderQueue;
class User;

class InMemoryStorage : public DataStorage
{
public:
    InMemoryStorage();
    ~InMemoryStorage() override;

    InMemoryStorage(const InMemoryStorage &) = delete;
    InMemoryStorage &operator=(const InMemoryStorage &) = delete;

private:
    QList<User *> users;       // Figure 1: InMemoryStorage -> User
    QList<MenuItem *> menu;    // Figure 1: InMemoryStorage -> MenuItem
    QList<Ingredient *> ingredients;   // Figure 1: InMemoryStorage -> Ingredient (shared by recipes)
    OrderQueue *kitchenQueue;  // Figure 1: InMemoryStorage -> OrderQueue
};

#endif // INMEMORYSTORAGE_H
