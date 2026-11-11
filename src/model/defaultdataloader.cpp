/*
 * DefaultDataLoader -- implementation
 *
 * TODO:
 *   - Create the menu, users and histories, and add them through
 *     DataStorage. [D1 p.1-2 Default System Data]
 *   - Work each customer's balances out from their history using Order's
 *     rules so they agree. [D1 p.2 Default System Data]
 *   - Copy the 11 names/usernames into the README test-user table. [D1 p.4-5
 *     Submission Requirements]
 */

#include "defaultdataloader.h"

#include "datastorage.h"

DefaultDataLoader::DefaultDataLoader(DataStorage &storage)
    : storage(storage)
{
}

void DefaultDataLoader::load()
{
    // TODO: create the default menu, users and order histories.
}
