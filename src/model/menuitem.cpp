/*
 * MenuItem -- implementation
 *
 * TODO:
 *   - Accessors for name, category, price and the recipe lines.
 */

#include "menuitem.h"

#include <QtAlgorithms>

#include "recipeingredient.h"

MenuItem::MenuItem() = default;

MenuItem::~MenuItem()
{
    qDeleteAll(recipe);   // only the recipe lines; the Ingredients belong to the storage
}
