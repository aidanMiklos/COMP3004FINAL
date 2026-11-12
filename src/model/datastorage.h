/*
 * DataStorage -- Model subsystem (abstract class, Bridge)
 *
 * Interface that every storage implements: InMemoryStorage in D1,
 * SQLiteStorage in D2. CafeDataStore and DefaultDataLoader only use this
 * interface.
 *
 * Spec notes:
 *   - D1 keeps the data as objects in memory. [D1 p.2 Default System Data]
 *   - D2 stores menu items, ingredients and inventory, customer and staff
 *     accounts, orders, the preparation queue and transactions in SQLite,
 *     loads them at launch and writes every change immediately. [Overview
 *     sec. 4.2]
 */

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

class DataStorage
{
public:
    virtual ~DataStorage() = default;

    // TODO: pure virtual methods every storage must provide, e.g.
    // (needs forward declarations and an InMemoryStorage implementation first)
    // virtual User *findUser(const QString &nameOrUsername) = 0;
    // virtual QList<MenuItem *> menuItems() const = 0;
    // virtual OrderQueue &orderQueue() = 0;
    // virtual void addUser(User *user) = 0;           // used by DefaultDataLoader
    // virtual void addMenuItem(MenuItem *item) = 0;   // used by DefaultDataLoader
    // virtual void addIngredient(Ingredient *ingredient) = 0;   // used by DefaultDataLoader
};

#endif // DATASTORAGE_H
