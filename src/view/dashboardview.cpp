/*
 * DashboardView -- implementation
 *
 * TODO:
 *   - Reload from DashboardController each time the page is shown; only one
 *     user is logged in at a time.
 */

#include "dashboardview.h"
#include "ui_dashboardview.h"
#include "viewtype.h"
#include "dashboardcontroller.h"
#include <QWidget>
#include <QLocale>


DashboardView::DashboardView(DashboardController *controller, QWidget *parent)
    : QWidget(parent), controller(controller), ui(new Ui::DashboardView)
{
    // TODO: account panel, current-order panel, history table.
    ui->setupUi(this);

    connect(ui->dashboardOrderBtn, &QPushButton::clicked, this, &DashboardView::createOrderBtnClicked);
    connect(ui->dashboardQueueBtn, &QPushButton::clicked, this, &DashboardView::orderQueueBtnClicked);
    connect(ui->dashboardSignOutBtn, &QPushButton::clicked, this, &DashboardView::signoutBtnClicked);
    connect(ui->dashboardUpdateInfoBtn, &QPushButton::clicked, this, &DashboardView::updateInfoBtnClicked);

}

void DashboardView::showEvent(QShowEvent *event) {

    // We first set the user's information
    displayClientInfo();

    // We then create the user's order history
    displayOrderHistory();

    // As well as their current order
    displayCurrentOrder();


}

void DashboardView::displayClientInfo() {

    // We request info from the controller
    CustomerDetails custDetails = controller->details();

    // Then we update the text of the label's to reflect the user currently signed in
    ui->dashboardNameLbl->setText("Name: " + custDetails.name);
    ui->dashboardAddressLbl->setText("Home Address: " + custDetails.homeAddress);
    ui->dashboardPointsAmountLbl->setText("Loyalty Points: " + QString::number(custDetails.loyaltyPoints));
    ui->dashboardEmailLbl->setText("Email: " + custDetails.email);
    ui->dashboardPointsNumLbl->setText("Loyalty Points #: " + custDetails.loyaltyNumber);
    ui->dashboardCreditAmountLbl->setText("Account Credit: " + QString::number(custDetails.creditCents));

}

void DashboardView::displayCurrentOrder() {

    // Finally, we update the user's current order, if they have one

    if (controller->hasCurrentOrder()){

        OrderSummary currentOrder = controller->currentOrder();

        ui->dashboardCurrentOrderLbl->setText("Current Order:");
        ui->dashboardCurrOrderInfoFrame->setVisible(true);

        ui->dashboardCOIDLbl->setText("Order ID: " + QString::number(currentOrder.orderId));
        ui->dashboardCOStatusLbl->setText("Current Status: " + currentOrder.status);
        ui->dashboardCOPurchasedLbl->setText("Items Purchased: " + currentOrder.items.join(", "));
        ui->dashboardPriceLbl->setText("Total: " + QLocale().toCurrencyString(currentOrder.totalCents/100.0));
        ui->dashboardUsedPointsLbl->setText("Loyalty Points Used: " + QString::number(currentOrder.pointsUsed));
        ui->dashboardEarnePointsLbl->setText("Loyalty Points Earned: " + QString::number(currentOrder.pointsEarned));
        ui->dashboardUsedCreditLbl->setText("Account Credit Used: " + QLocale().toCurrencyString(currentOrder.creditUsedCents/100.0));


    } else {

        ui->dashboardCurrentOrderLbl->setText("No current order");
        ui->dashboardCurrOrderInfoFrame->setVisible(false);

    }

}

void DashboardView::visualUpdateUserType(const QString &userType) {

    // When the user logs in, we adjust the visual to reflect who is visiting
    if(userType == "System Administrator") {

        ui->dashboardUserLbl->setText("System Admin");

    } else {

        ui->dashboardUserLbl->setText(userType);

    }

    // Only kitchen staff can see the order queue
    if (userType != "Kitchen Staff"){

        ui->dashboardQueueBtn->setVisible(false);

    } else {

        ui->dashboardQueueBtn->setVisible(true);

    }

    if (userType != "Customer"){

        ui->dashboardOrderBtn->setVisible(false);
        ui->dashboardCustomerOnlyCont->setVisible(false);
        ui->dashboardMainLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    } else {

        ui->dashboardOrderBtn->setVisible(true);
        ui->dashboardCustomerOnlyCont->setVisible(true);
        ui->dashboardMainLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    }

}

void DashboardView::displayOrderHistory() {

    while (QLayoutItem *entryLayout = ui->orderHistoryEntriesCont->takeAt(0)){

        // We then check if the returned item is a widget. We only really do this as to prevent calls to nullptr.
        if(QWidget *entryWidget = entryLayout->widget()){

            // Then delete it
            entryWidget->deleteLater();

        }

        delete entryLayout;

    }

    // Now we generate entries for the current user's order history
    QList<OrderSummary> orderHistory = controller->orderHistory();

    for (OrderSummary currentHistOrder : orderHistory){

        // First we make a container for this entry
        QWidget *entryContainer = new QWidget;

        // Set it to a grid container
        QGridLayout *gridLayout = new QGridLayout(entryContainer);

        // Now we add labels about the given order's information
        gridLayout->addWidget(new QLabel("Order ID: " + QString::number(currentHistOrder.orderId)), 0, 0);
        gridLayout->addWidget(new QLabel("Status: " + currentHistOrder.status), 0, 1);
        gridLayout->addWidget(new QLabel("Items Purchased: " + QString::number(currentHistOrder.items.size())), 0, 2);
        gridLayout->addWidget(new QLabel("Total: " + QLocale().toCurrencyString(currentHistOrder.totalCents/100.0)), 1, 0);
        // If the loyalty points were used...
        if(currentHistOrder.pointsUsed != 0){

            gridLayout->addWidget(new QLabel("Loyalty Points Used: " + QString::number(currentHistOrder.pointsUsed)), 1, 1);

        } else {

            gridLayout->addWidget(new QLabel("Loyalty Points Earned: "+ QString::number(currentHistOrder.pointsEarned)), 1, 1);

        }

        gridLayout->addWidget(new QLabel("Account Credit Used: " + QLocale().toCurrencyString(currentHistOrder.creditUsedCents/100.0)), 1, 2);

        // Then we add this entry to the client's order history
        ui->orderHistoryEntriesCont->addWidget(entryContainer);

        // To separate the entries, we add a little divider
        QFrame *divider = new QFrame();
        divider->setFrameShape(QFrame::NoFrame);
        divider->setStyleSheet("background-color: rgb(222, 221, 218);");
        divider->setFixedWidth(1);

        ui->orderHistoryEntriesCont->addWidget(divider);

    }

}

// ----------------- PRIVATE SLOTS -----------------

void DashboardView::updateInfoBtnClicked() {

    if (controller->updateContact(ui->dashboardEmailInput->text(), ui->dashboardAddressInput->text())) {

        // If the provided information was acceptable for updating, we refresh the clients information
        displayClientInfo();

        // And empty the update text inputs
        ui->dashboardEmailInput->setText("");
        ui->dashboardAddressInput->setText("");

    }

}

void DashboardView::createOrderBtnClicked() {

    emit requestViewChange(ViewType::MakeOrderView);

}

void DashboardView::orderQueueBtnClicked() {

    emit requestViewChange(ViewType::OrderQueueView);

}

void DashboardView::signoutBtnClicked() {

    emit requestViewChange(ViewType::LoginView);

}

