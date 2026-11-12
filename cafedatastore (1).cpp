#include "cafedatastore.h"
#include "datastorage.h"
#include "defaultdataloader.h"
#include "inmemorystorage.h"

CafeDataStore&CafeDataStore::instance()
{
    static CafeDataStore store;
    return store;
}

CafeDataStore::CafeDataStore():
    storage(new InMemoryStorage){
    DefaultDataLoader(*storage).load();

}

CafeDataStore::~CafeDataStore(){
    delete storage;
}

User* CafeDataStore::findUser(const QString &nameOrUsername){
    return storage->findUser(nameOrUsername);
}

QList<MenuItem*> CafeDataStore::menuItems()const{
    return storage->menuItems();
}

OrderQueue& CafeDataStore::orderQueue(){
    return storage->orderQueue();
}
