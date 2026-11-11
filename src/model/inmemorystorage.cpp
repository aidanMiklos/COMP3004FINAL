/*
 * InMemoryStorage -- implementation
 *
 * TODO:
 *   - Implement each DataStorage method with QList look-ups and appends.
 *   - The destructor deletes the objects this storage owns.
 */

#include "inmemorystorage.h"

#include <QtAlgorithms>

#include "menuitem.h"
#include "orderqueue.h"
#include "user.h"

InMemoryStorage::InMemoryStorage()
    : kitchenQueue(new OrderQueue)
{
}

InMemoryStorage::~InMemoryStorage()
{
    qDeleteAll(users);
    qDeleteAll(menu);
    delete kitchenQueue;
}
