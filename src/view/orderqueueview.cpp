/*
 * OrderQueueView -- implementation
 *
 * TODO:
 *   - Fill the list from KitchenController, oldest first; double-click or a
 *     button opens the details dialog. [D1 p.3 Feature 5]
 */

#include "orderqueueview.h"
#include "ui_orderqueueview.h"
#include "viewtype.h"

#include "orderdetailsview.h"
#include "kitchencontroller.h"

OrderQueueView::OrderQueueView(KitchenController *controller, QWidget *parent)
    : QWidget(parent), controller(controller),
      detailsDialog(new OrderDetailsView(controller, this)),
      ui(new Ui::OrderQueueView)
{
    // TODO: queue table (number, customer, date/time) and Open button.
    ui->setupUi(this);

    connect(ui->queueDashboardBtn, &QPushButton::clicked, this, &OrderQueueView::dashboardBtnClicked);
    connect(detailsDialog, &OrderDetailsView::signalOrderSetCompleted, this, &OrderQueueView::orderSetCompleted);
    connect(ui->orderQueueSignOutBtn, &QPushButton::clicked, this, &OrderQueueView::signoutBtnClicked);
}

void OrderQueueView::visualUpdateUserType(const QString &userType) {

    ui->orderQueueUserLbl->setText(userType);

}

void OrderQueueView::showEvent(QShowEvent *event) {

    // Simply call resetVisuals
    resetVisuals();

}

void OrderQueueView::resetVisuals() {

    // Since views are created on start-up and then just reused, we need to delete the queue from the last visit that is still here\
    // First we check if there are any entries by using takeAt(), which removes the layout at the specified index
    // If there are none to remove, it returns nullptr and the while loop ends
    while (QLayoutItem *entryLayout = ui->queueEntriesCont->takeAt(0)){

        // We then check if the returned item is a widget. We only really do this as to prevent calls to nullptr.
        if(QWidget *entryWidget = entryLayout->widget()){

            // Then delete it
            entryWidget->deleteLater();

        }

        delete entryLayout;

    }

    QList<QueueEntry> queueItems = controller->queue();

    for (QueueEntry currentEntry : queueItems){

        // First we make a container for this entry
        QWidget *entryContainer = new QWidget;

        // Set it to a grid container
        QGridLayout *gridLayout = new QGridLayout(entryContainer);

        // Now we add labels about the given order's information
        gridLayout->addWidget(new QLabel("Order ID: " + QString(currentEntry.orderId)), 0, 0);
        gridLayout->addWidget(new QLabel("Customer Name: " + currentEntry.customerName), 0, 1);
        gridLayout->addWidget(new QLabel("Order Date and Time: " + currentEntry.placedAt), 0, 2);

        // For the order queue, we need to be able to view the info about each order, so we add a button for that
        QPushButton *detailsBtn = new QPushButton("View Details", this);
        // Link the button so that it can actually call a function
        int localOrderId = currentEntry.orderId;
        connect(detailsBtn, &QPushButton::clicked, this, [this, localOrderId] ()
            {
                OrderQueueView::orderDetailsBtnClicked(localOrderId);
            }
        );


        // Then add it to the layout
        gridLayout->addWidget(detailsBtn, 0, 3);

        // Then we add this entry to the client's order history
        ui->queueEntriesCont->addWidget(entryContainer);
    }

}


void OrderQueueView::dashboardBtnClicked(){

    emit requestViewChange(ViewType::DashboardView);

}

void OrderQueueView::signoutBtnClicked(){

    emit requestViewChange(ViewType::LoginView);

}

void OrderQueueView::orderDetailsBtnClicked(int orderId){

    // We give the ID of the requested order to the orderDetailsView
    detailsDialog->requestedOrderId(orderId);

    // Then show it to the user. Using exec() means the user can't do anything besides interact with the order details view, and when closing will delete itself from memory
    detailsDialog->show();

}

void OrderQueueView::orderSetCompleted() {

    // When an order is set completed, we need to close the order details dialogue box
    detailsDialog->hide();

    // Then we reset the visuals to reflect the new queue that lacks the just completed order
    resetVisuals();

}

