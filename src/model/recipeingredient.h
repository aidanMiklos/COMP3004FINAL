/*
 * RecipeIngredient -- Model subsystem (entity class)
 *
 * One line of a menu item's recipe: which Ingredient, and how much of it
 * this item uses.
 *
 * Spec notes:
 *   - Each menu item references its ingredients and the quantity of each.
 *     [D1 p.2 Default System Data]
 *   - Kitchen staff see the items and their ingredients for each order.
 *     [Overview sec. 2, Staff: Kitchen]
 */

#ifndef RECIPEINGREDIENT_H
#define RECIPEINGREDIENT_H

class Ingredient;

class RecipeIngredient
{
public:
    RecipeIngredient();

private:
    Ingredient *ingredient = nullptr;   // Figure 1: RecipeIngredient -> Ingredient
};

#endif // RECIPEINGREDIENT_H
