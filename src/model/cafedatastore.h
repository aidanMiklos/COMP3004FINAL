/*
 * CafeDataStore -- Model subsystem (Facade + Singleton)
 *
 * The only Model class that controllers talk to. There is exactly one,
 * reached with CafeDataStore::instance(). It passes each request on to the
 * DataStorage it holds, so the way data is stored can change without
 * touching any controller (Bridge, Figure 1).
 *
 * Spec notes:
 *   - All data is kept in memory as objects; marks are deducted for not
 *     storing data as objects. [D1 p.2 Default System Data]
 *   - D1 has no database or file persistence. [D1 p.1 Overview; D1 p.4
 *     Excluded from this Prototype]
 *   - D2 must store data persistently in SQLite, which is why storage sits
 *     behind the abstract DataStorage. [Overview sec. 4.2]
 *   - The code must use polymorphism and design patterns (here: Facade,
 *     Singleton, Bridge). [D1 p.4 Implementation Requirements]
 */

#ifndef CAFEDATASTORE_H
#define CAFEDATASTORE_H

class DataStorage;

class CafeDataStore
{
public:
    static CafeDataStore &instance();

    CafeDataStore(const CafeDataStore &) = delete;
    CafeDataStore &operator=(const CafeDataStore &) = delete;

    // TODO: facade methods that forward to storage, e.g.
    //   User *findUser(const QString &nameOrUsername);
    //   QList<MenuItem *> menuItems() const;
    //   OrderQueue &orderQueue();

private:
    CafeDataStore();
    ~CafeDataStore();

    DataStorage *storage;   // Figure 1: CafeDataStore -> DataStorage (Bridge)
};

#endif // CAFEDATASTORE_H
