/*
 * DefaultDataLoader -- Model subsystem
 *
 * Fills a DataStorage with the required default data at startup. It works
 * through the abstract DataStorage, so the same loader fills InMemoryStorage
 * now and an empty SQLite database in D2.
 *
 * Spec notes:
 *   - Menu: at least 10 items, with at least 3 sandwiches, 4 hot beverages
 *     and 3 cold beverages; each has a name, category, price, and its
 *     ingredients with the quantity of each. [D1 p.1-2 Default System Data]
 *   - 11 users: 5 customers, 2 kitchen staff, 2 cashiers, 1 manager, 1
 *     system administrator. [D1 p.2 Default System Data]
 *   - Customers: name, unique username, unique loyalty points number, email,
 *     home address, points balance, account credit balance, and 5 orders in
 *     their history. [D1 p.2 Default System Data]
 *   - Staff: name, unique username, unique staff ID. [D1 p.2 Default System
 *     Data]
 *   - History orders are Picked Up or Cancelled, with order number, items,
 *     final price with tax, amount charged, points used, credit used, points
 *     earned, status, and online or in person. [D1 p.2 Default System Data]
 *   - Across all customers, include at least: one cancelled order paid with
 *     points and credit, one paid with points, one paid with credit, and one
 *     that earned points. [D1 p.2 Default System Data]
 *   - Balances must agree with the order history. [D1 p.2 Default System
 *     Data]
 */

#ifndef DEFAULTDATALOADER_H
#define DEFAULTDATALOADER_H

class DataStorage;

class DefaultDataLoader
{
public:
    explicit DefaultDataLoader(DataStorage &storage);

    void load();

private:
    DataStorage &storage;   // Figure 1: DefaultDataLoader -> DataStorage
};

#endif // DEFAULTDATALOADER_H
