#ifndef RECIPEINGREDIENT_H
#define RECIPEINGREDIENT_H
#include "ingredient.h"


class RecipeIngredient
{
public:
    RecipeIngredient(Ingredient *ingredient, int quantity);
    Ingredient* ingredient()const;
    int quantity() const;

private:
    Ingredient *m_ingredient;
    int m_quantity;
};

#endif // RECIPEINGREDIENT_H
