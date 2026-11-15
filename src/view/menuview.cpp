/*
 * MenuView -- implementation
 *
 * TODO:
 *   - Ask MenuController for the items by category and fill a tree or list
 *     widget. [D1 p.3 Feature 2]
 */

#include "menuview.h"
#include "ui_menuview.h"
#include "menucontroller.h"
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
    displayMenu();

}

void MenuView::displayMenu() {

    // First we must delete the widgets that are on the menu
    while (QLayoutItem *entryLayout = ui->menuItemsCont->takeAt(0)){

        // We then check if the returned item is a widget. We only really do this as to prevent calls to nullptr.
        if(QWidget *entryWidget = entryLayout->widget()){

            // Then delete it
            entryWidget->deleteLater();

        }

        delete entryLayout;

    }

    // Now we must construct each category on the menu, including its items
    for (QString currentCategory : controller->categories()){

        // We add a label that will separate this category from the rest
        QLabel *categoryLabel = new QLabel("Category: " + currentCategory);
        ui->menuItemsCont->addWidget(categoryLabel);

        // As well as a nice little visual divider
        QFrame *divider = new QFrame;
        divider->setFixedHeight(1);
        divider->setStyleSheet("background-color: #DEDDDA;");
        divider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->menuItemsCont->addWidget(divider);

        // Then we loop over each item in that category
        for (MenuEntry currentEntry : controller->itemsIn(currentCategory)){

            // First we make a container for this entry
            QWidget *entryContainer = new QWidget;

            // Set it to a grid container
            QGridLayout *gridLayout = new QGridLayout(entryContainer);
            gridLayout->setContentsMargins(0,9,9,9);

            // Now we add labels about the given order's information
            gridLayout->addWidget(new QLabel("Item Name: " + currentEntry.name), 0, 0);
            gridLayout->addWidget(new QLabel("Price: " + QLocale().toCurrencyString(currentEntry.priceCents/100.0)), 0, 1);
            gridLayout->addWidget(new QLabel("Available"), 0, 2);

            // We also add a button to add the given menu item to the client's order
            QPushButton *addBtn = new QPushButton("Add to Order", this);
            // Link the button so that it can actually call a function
            QString localEntryName = currentEntry.name;
            connect(addBtn, &QPushButton::clicked, this, [this, localEntryName] ()
                {
                    MenuView::addItemBtnClicked(localEntryName);
                }
            );

            gridLayout->addWidget(addBtn, 0, 3);

            // Then we add this entry to the menu
            ui->menuItemsCont->addWidget(entryContainer);

        }

    }

}

void MenuView::addItemBtnClicked(const QString &menuItemName) {

    // When the add button is clicked, we emit what was clicked, and the makeorderview will pick up on it
    emit addItem(menuItemName);

}
