#include "recipeingredient.h"

RecipeIngredient::RecipeIngredient(Ingredient *ingredient, int quantity):
    m_ingredient(ingredient), m_quantity(quantity >0 ? quantity : 0)
{
}

Ingredient* RecipeIngredient::ingredient()const
{
    return m_ingredient;
}

int RecipeIngredient::quantity()const
{
    return m_quantity;
}
