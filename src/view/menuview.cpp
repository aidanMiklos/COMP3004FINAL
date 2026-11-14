/*
 * MenuView -- implementation
 *
 * TODO:
 *   - Ask MenuController for the items by category and fill a tree or list
 *     widget. [D1 p.3 Feature 2]
 */

#include "menuview.h"
#include "ui_menuview.h"
#include <QLabel>
#include <QPushButton>

MenuView::MenuView(MenuController *controller, QWidget *parent)
    : QWidget(parent), controller(controller), ui(new Ui::MenuView)
{
       ui->setupUi(this);
    // TODO: category tree or list.
}

void MenuView::showEvent(QShowEvent *event) {

    // Whenever the menu becomes visible, we need to refresh it to reflect the menu and its items, if they have been updated.

    // So first we must delete the widgets that are on the menu
    while (QLayoutItem *entryLayout = ui->menuItemsCont->takeAt(0)){

        // We then check if the returned item is a widget. We only really do this as to prevent calls to nullptr.
        if(QWidget *entryWidget = entryLayout->widget()){

            // Then delete it
            entryWidget->deleteLater();

        }

        delete entryLayout;

    }

    // Then we add an entry for each menu item
    for (int i = 0; i < 15; ++i){

        // First we make a container for this entry
        QWidget *entryContainer = new QWidget;

        // Set it to a grid container
        QGridLayout *gridLayout = new QGridLayout(entryContainer);

        // Now we add labels about the given order's information
        gridLayout->addWidget(new QLabel("Item Name: Test"), 0, 0);
        gridLayout->addWidget(new QLabel("Price: burger"), 0, 1);
        gridLayout->addWidget(new QLabel("Available"), 0, 2);

        // We also add a button to add the given menu item to the client's order
        QPushButton *addBtn = new QPushButton("Add to Order", this);
        // Link the button so that it can actually call a function
        QString test = "test";
        connect(addBtn, &QPushButton::clicked, this, [this, test] ()
            {
                MenuView::addItemBtnClicked(test);
            }
        );

        gridLayout->addWidget(addBtn, 0, 3);

        // Then we add this entry to the client's order history
        ui->menuItemsCont->addWidget(entryContainer);
    }

}

void MenuView::addItemBtnClicked(const QString &menuItemName) {



}
