/*
 * MenuController -- Controller subsystem (control class)
 *
 * Gives MenuView the menu, grouped by category.
 *
 * Spec notes:
 *   - Display menu items grouped by category. [D1 p.3 Feature 2]
 *   - Every menu item has a name, category and price. [D1 p.2 Default System
 *     Data]
 */

#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <QList>
#include <QString>
#include <QStringList>

class CafeDataStore;

struct MenuEntry
{
    QString name;
    int priceCents = 0;
};

class MenuController
{
public:
    MenuController();

    // TODO: operations for the views. Pass the logged-in username in
    //       (MainWindow gets it from AccountController) and return plain
    //       data (QString, numbers), not model pointers.

    QStringList categories() const;
    QList<MenuEntry> itemsIn(const QString &category) const;

private:
    CafeDataStore &store;
};

#endif // MENUCONTROLLER_H
