/*
 * MenuController -- implementation
 *
 * TODO:
 *   - Read the items through CafeDataStore and group them by category. [D1
 *     p.3 Feature 2]
 */

#include "menucontroller.h"

#include "cafedatastore.h"

MenuController::MenuController()
    : store(CafeDataStore::instance())
{
}
