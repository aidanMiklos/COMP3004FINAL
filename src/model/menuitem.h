/*
 * MenuItem -- Model subsystem (entity class)
 *
 * One item on the menu. Holds its recipe lines (Figure 1: MenuItem ->
 * RecipeIngredient), the same way an Order holds its OrderItems.
 *
 * Spec notes:
 *   - Each menu item has a name, category and price. [D1 p.2 Default System
 *     Data]
 *   - Each menu item references the ingredients needed to prepare it and the
 *     quantity of each. [D1 p.2 Default System Data]
 *   - The cafe serves sandwiches and hot and cold beverages. [Overview sec.
 *     1]
 *   - Sold-out marking is excluded from D1. [D1 p.4 Excluded from this
 *     Prototype]
 */

#ifndef MENUITEM_H
#define MENUITEM_H

#include <QList>

class RecipeIngredient;

class MenuItem
{
public:
    MenuItem();

private:
    QList<RecipeIngredient *> recipe;   // Figure 1: MenuItem -> RecipeIngredient
};

#endif // MENUITEM_H
