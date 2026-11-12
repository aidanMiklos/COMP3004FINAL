/*
 * OrderQueueView -- implementation
 *
 * TODO:
 *   - Fill the list from KitchenController, oldest first; double-click or a
 *     button opens the details dialog. [D1 p.3 Feature 5]
 */

#include "orderqueueview.h"
#include "ui_orderqueueview.h"

#include "orderdetailsview.h"

OrderQueueView::OrderQueueView(KitchenController *controller, QWidget *parent)
    : QWidget(parent), controller(controller),
      detailsDialog(new OrderDetailsView(controller, this)),
      ui(new Ui::OrderQueueView)
{
    // TODO: queue table (number, customer, date/time) and Open button.
    ui->setupUi(this);
}
