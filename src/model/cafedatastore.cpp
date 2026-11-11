/*
 * CafeDataStore -- implementation
 *
 * TODO:
 *   - instance(): create the one store on first use.
 *   - Constructor: create the storage and fill it with the default data. In
 *     D2, swap InMemoryStorage for SQLiteStorage on that one line. [D1 p.1-2
 *     Default System Data]
 *   - Add one forwarding method per operation the controllers need.
 */

#include "cafedatastore.h"

#include "defaultdataloader.h"
#include "inmemorystorage.h"

CafeDataStore &CafeDataStore::instance()
{
    static CafeDataStore store;   // created on first use, destroyed at program exit
    return store;
}

CafeDataStore::CafeDataStore()
    : storage(new InMemoryStorage)   // D2: new SQLiteStorage
{
    DefaultDataLoader(*storage).load();   // D2: only when the database is empty
}

CafeDataStore::~CafeDataStore()
{
    delete storage;
}
