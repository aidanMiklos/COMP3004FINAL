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
#include <QWidget>
#include <QDebug>


DashboardView::DashboardView(DashboardController *controller, QWidget *parent)
    : QWidget(parent), controller(controller), ui(new Ui::DashboardView)
{
    // TODO: account panel, current-order panel, history table.
    ui->setupUi(this);

    connect(ui->dashboardOrderBtn, &QPushButton::clicked, this, &DashboardView::createOrderBtnClicked);
    connect(ui->dashboardQueueBtn, &QPushButton::clicked, this, &DashboardView::orderQueueBtnClicked);
}

//void DashboardView::displayUsername(const QString &name)
//{

//    ui->dashboardMainLbl->setText("Welcome " + name);

//}

void DashboardView::showEvent(QShowEvent *event) {

    // Here we would request info from the Dash
//    temp funcs for now

    int accType = 2;
    QString accTypeLbl;

    switch(accType){

        default:
            accTypeLbl = "Customer";
        break;

        case 1:
            accTypeLbl = "Cashier";
        break;

        case 2:
            accTypeLbl = "Kitchen Staff";
        break;

        case 3:
            accTypeLbl = "Manager";
        break;

        case 4:
            accTypeLbl = "Administrator";
        break;

    }

    ui->dashboardUserLbl->setText(accTypeLbl);

    for (int i = 0; i < 5; ++i){

        // First we make a container for this entry
        QWidget *entryContainer = new QWidget;

        // Set it to a grid container
        QGridLayout *gridLayout = new QGridLayout(entryContainer);

        // Now we add labels about the given order's information
        gridLayout->addWidget(new QLabel("Order ID: "), 0, 0);
        gridLayout->addWidget(new QLabel("Status: "), 0, 1);
        gridLayout->addWidget(new QLabel("Items Purchased: "), 0, 2);
        gridLayout->addWidget(new QLabel("Total: "), 1, 0);
        gridLayout->addWidget(new QLabel("Loyalty Points Used/Earned: "), 1, 1);
        gridLayout->addWidget(new QLabel("Account Credit Received/Used: "), 1, 2);

        // Then we add this entry to the client's order history
        ui->orderHistoryEntriesCont->addWidget(entryContainer);
    }

}

// ----------------- PRIVATE SLOTS -----------------

void DashboardView::createOrderBtnClicked() {

    emit requestViewChange(ViewType::MakeOrderView);

}

void DashboardView::orderQueueBtnClicked() {

    emit requestViewChange(ViewType::OrderQueueView);

}



//void DashboardView::signoutBtnClicked() {

//}

