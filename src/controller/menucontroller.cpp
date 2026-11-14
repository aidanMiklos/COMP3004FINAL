/*
 * MenuController -- implementation
 *
 * TODO:
 *   - Read the items through CafeDataStore and group them by category. [D1
 *     p.3 Feature 2]
 */

#include "menucontroller.h"

#include "cafedatastore.h"
#include "menuitem.h"

MenuController::MenuController()
    : store(CafeDataStore::instance())
{
}

QStringList MenuController::categories() const
{
    QStringList result;
    for (const MenuItem *item : store.menuItems()) { // Get the category of each item and add it to result
        if (!result.contains(item->category()))
            result.append(item->category()); 
    }
    return result;
}

QList<MenuEntry> MenuController::itemsIn(const QString &category) const
{
    QList<MenuEntry> result;
    for (const MenuItem *item : store.menuItems()) { // Get the items in the specified category and add them to result
        if (item->category() == category) {
            MenuEntry entry;
            entry.name = item->name();
            entry.priceCents = item->priceCents();
            result.append(entry);
        }
    }
    return result;
}
