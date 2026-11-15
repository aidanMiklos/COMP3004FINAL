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
#include "ordercontroller.h"

#include "menuview.h"
#include "viewtype.h"
#include <QtDebug>

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
    // Connect the menu view with its function
    connect(menuView, &MenuView::addItem, this, &MakeOrderView::custItemRequested);
    // Connect the signout button with its function
    connect(ui->makeOrderSignOutBtn, &QPushButton::clicked, this, &MakeOrderView::signoutBtnClicked);


}

void MakeOrderView::visualUpdateUserType(const QString &userType) {

    ui->dashboardUserLbl_2->setText(userType);

}

void MakeOrderView::showEvent(QShowEvent *event) {

    // When the make order screen becomes visible, we update the checkout box to reflect the user's current order, or lack thereof
    updateCheckout();

    // Additionally, we make an order for the customer to use. If they already have an order, we warn them they can't make two at the same time
    if(!controller->startOrder()) {

        ui->makeOrderWarningLbl->setVisible(true);

    } else {

        ui->makeOrderWarningLbl->setVisible(false);

    }

}

void MakeOrderView::custItemRequested(const QString &menuItemName) {

    qDebug() << "custItemRequested, checking if make orer possible..." << controller->canPlaceOrder();

    // First we check if the user can even place an order
    if(controller->canPlaceOrder()){

        qDebug() << "custItemRequested fired";

        // Then we add the item. Since we don't have the ability to add in bulk, it will always be 1
        controller->addItem(menuItemName, 1);

        // And ask the checkout to update itself to reflect the item added
        updateCheckout();

    }

}

void MakeOrderView::updateCheckout() {

    // We retrieve the current breakdown of the users current order from the controller
    PriceBreakdown breakdown = controller->breakdown(controller->availablePoints(),controller->availableCreditCents());

    qDebug() << "updating checkout: " << QLocale().toCurrencyString(breakdown.subtotalCents/100.0);

    ui->makeOrderSubTotalLbl->setText("Subtotal: " + QLocale().toCurrencyString(breakdown.subtotalCents/100.0));
    ui->makeOrderTaxLbl->setText("Tax: " + QLocale().toCurrencyString(breakdown.taxCents/100.0));
    ui->makeOrderPointsUsedLbl->setText("Loyalty Points Used: " + QString::number(breakdown.pointsUsed));
    ui->makeOrderCreditUsedLbl->setText("Account Credit Used: " + QLocale().toCurrencyString(breakdown.creditUsedCents/100.0));
    ui->makeOrderTotalLbl->setText("Total: " + QLocale().toCurrencyString(breakdown.totalCents/100.0));

}

void MakeOrderView::checkoutBtnClicked() {

    // Request username from mainwindow, submit information to controller
    controller->submitOrder(controller->availablePoints(),controller->availableCreditCents());
    updateCheckout();

}

void MakeOrderView::dashboardBtnClicked() {

    emit requestViewChange(ViewType::DashboardView);

}

void MakeOrderView::signoutBtnClicked() {

    emit requestViewChange(ViewType::LoginView);

}
