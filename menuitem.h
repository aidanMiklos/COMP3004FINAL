#ifndef MENUITEM_H
#define MENUITEM_H
#include <QString>
#include <QVector>
#include "recipeingredient.h"

class MenuItem
{
public:
    MenuItem(const QString &name, int priceCents);
    QString name()const;
    int priceCents()const;
    bool avaliable()const;


    void setAvaliable(bool avaliable);
    void addIngredient(const RecipeIngredient &ingredient);
    QVector<RecipeIngredient> ingredients() const;
private:
    QString m_name;
    int m_priceCents;
    bool m_avaliable;
    QVector<RecipeIngredient> m_ingredients;
};

#endif // MENUITEM_H
