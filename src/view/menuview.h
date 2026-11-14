/*
 * MenuView -- View subsystem (boundary class)
 *
 * Shows the cafe menu. Used as its own page and also embedded in
 * MakeOrderView for picking items (Figure 1: MakeOrderView -> MenuView).
 *
 * Spec notes:
 *   - Display the menu items grouped by category. [D1 p.3 Feature 2]
 *   - The menu has sandwiches, hot beverages and cold beverages. [D1 p.1
 *     Default System Data]
 *   - Customers see each item's name and price. [Overview sec. 2, Online
 *     Order]
 *   - Availability and sold-out marking are excluded from D1 (no inventory).
 *     [D1 p.4 Excluded from this Prototype]
 */

#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MenuView; }
QT_END_NAMESPACE

class MenuController;

class MenuView : public QWidget
{
    Q_OBJECT

public:
    explicit MenuView(MenuController *controller, QWidget *parent = nullptr);

private:
    MenuController *controller;   // Figure 1: MenuView -> MenuController

    Ui::MenuView *ui;
};

#endif // MENUVIEW_H
