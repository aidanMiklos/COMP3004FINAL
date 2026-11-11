/*
 * Ingredient -- Model subsystem (entity class)
 *
 * An ingredient itself (for example bread), shared by every recipe line that
 * uses it.
 *
 * Spec notes:
 *   - Each menu item lists its ingredients with quantities. [D1 p.2 Default
 *     System Data]
 *   - D2: when an ingredient runs short, every menu item that needs it
 *     becomes sold out. That needs one shared object per ingredient with a
 *     stock level. [Overview sec. 3]
 *   - Inventory tracking and ingredient deduction are excluded from D1. [D1
 *     p.4 Excluded from this Prototype]
 */

#ifndef INGREDIENT_H
#define INGREDIENT_H

class Ingredient
{
public:
    Ingredient();
};

#endif // INGREDIENT_H
