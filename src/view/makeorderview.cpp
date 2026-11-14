/*
 * MakeOrderView -- implementation
 *
 * TODO:
 *   - Refresh the breakdown whenever items, points or credit change. The
 *     numbers come from OrderController (which asks Order); never calculate
 *     prices in the view. [D1 p.3 Feature 3]
 */

#include "makeorderview.h"
#include "ui_makeorderview.h"

#include "menuview.h"
#include "viewtype.h"

MakeOrderView::MakeOrderView(OrderController *controller, MenuController *menuController, QWidget *parent)
    : QWidget(parent), controller(controller),
      menuView(new MenuView(menuController, this)),
      ui(new Ui::MakeOrderView)
{
    // TODO: lay out menuView, quantity, points and credit inputs, breakdown, Submit.
    ui->setupUi(this);

    // Place the menu widget within this view
    ui->makeOrderMenuCont->layout()->addWidget(menuView);
    // Connect the checkout button with its function
    connect(ui->makeOrderCheckoutBtn, &QPushButton::clicked, this, &MakeOrderView::checkoutBtnClicked);
    // Connect the dashboard button with its function
    connect(ui->makeOrderDashboardBtn, &QPushButton::clicked, this, &MakeOrderView::dashboardBtnClicked);


}

void MakeOrderView::custItemRequested(const QString &menuItemName) {



}

void MakeOrderView::checkoutBtnClicked() {

    // Request username from mainwindow, submit information to controller

}

void MakeOrderView::dashboardBtnClicked() {

    emit requestViewChange(ViewType::DashboardView);

}

