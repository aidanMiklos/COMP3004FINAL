#include "menuitem.h"

MenuItem::MenuItem(const QString &name, int priceCents):m_name(name),
    m_priceCents(priceCents >= 0? priceCents :0), m_avaliable(true)
{
}

QString MenuItem::name() const
{
    return m_name;
}

int MenuItem::priceCents() const
{
    return m_priceCents;
}

bool MenuItem::avaliable()const
{
    return m_avaliable;
}

void MenuItem::setAvaliable(bool avaliable)
{
    m_avaliable = avaliable;
}

void MenuItem::addIngredient(const RecipeIngredient &ingredient){
    m_ingredients.append(ingredient);
}

QVector<RecipeIngredient> MenuItem::ingredients()const{
    return m_ingredients;
}
