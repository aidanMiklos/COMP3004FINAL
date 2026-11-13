#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <QString>


class Ingredient
{
public:
    Ingredient(const QString &name, int stockQuantity);
    QString name() const;
    int stockQuantity() const;
    void addStock(int quantity);
    bool useStock(int quantity);

private:
    QString m_name;
    int m_stockQuantity;
};

#endif // INGREDIENT_H
