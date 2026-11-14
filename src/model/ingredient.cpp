#include "ingredient.h"

Ingredient::Ingredient(const QString &name, int stockQuantity)
    : m_name(name), m_stockQuantity(stockQuantity >= 0 ? stockQuantity: 0)
{
}

QString Ingredient::name()const
{
    return m_name;
}

int Ingredient::stockQuantity()const
{
    return m_stockQuantity;
}

void Ingredient::addStock(int quantity)
{
    if(quantity > 0){
        m_stockQuantity += quantity;
}
}
bool Ingredient::useStock(int quantity)
{
    if(quantity <= 0 || quantity > m_stockQuantity){
        return false;
    }

    m_stockQuantity -= quantity;
    return true;
}
