/*
 * OrderDetailsView -- implementation
 *
 * TODO:
 *   - Mark Completed calls KitchenController, then the dialog closes and the
 *     queue refreshes. [D1 p.3 Feature 7]
 */

#include "orderdetailsview.h"
#include "ui_orderdetailsview.h"

OrderDetailsView::OrderDetailsView(KitchenController *controller, QWidget *parent)
    : QDialog(parent), controller(controller), orderId(-1),
      ui(new Ui::OrderDetailsView)
{
    // TODO: order header, items with ingredients, Mark Completed button.
    ui->setupUi(this);

    setWindowTitle("Order Details");
}

void OrderDetailsView::requestedOrderId(int orderId) {

    // We update all labels when this function is called, and it is always called when the view details button is clicked.
    ui->orderDetailsMainLbl->setText("Details for Order ID: " + QString::number(orderId));
    ui->orderDetailsCustNameLbl->setText("Customer Name: Henri");
    ui->orderDetailsPlacedLbl->setText("Placed At: Friday");
    ui->orderDetailsStatusLbl->setText("Status: In Progress");

    // Then we assign the orderID
    this->orderId = orderId;

    // Now we need to display each item in the order

    // First we delete any widgets in the container from when it was visible before. If it was, at least
    while (QLayoutItem *entryLayout = ui->orderDetailsItemsEntriesCont->takeAt(0)){

        // We then check if the returned item is a widget. We only really do this as to prevent calls to nullptr.
        if(QWidget *entryWidget = entryLayout->widget()){

            // Then delete it
            entryWidget->deleteLater();

        }

        delete entryLayout;

    }

    for (int i = 0; i < 200; ++i){

        // First we make a container for this entry
        QWidget *entryContainer = new QWidget;

        // Set it to a grid container
        QGridLayout *gridLayout = new QGridLayout(entryContainer);

        // Now we add labels about the given order's information
        gridLayout->addWidget(new QLabel("Item name: burger"), 0, 0);
        gridLayout->addWidget(new QLabel("Quantity: 500"), 0, 1);
        gridLayout->addWidget(new QLabel("Ingredients: "), 1, 0);

        // Then we add this entry to the client's order history
        ui->orderDetailsItemsEntriesCont->addWidget(entryContainer);
    }

}


void OrderDetailsView::completeBtnClicked(){

    // Send info ot the controller using orderId

}
