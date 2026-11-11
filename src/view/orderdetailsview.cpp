/*
 * OrderDetailsView -- implementation
 *
 * TODO:
 *   - Mark Completed calls KitchenController, then the dialog closes and the
 *     queue refreshes. [D1 p.3 Feature 7]
 */

#include "orderdetailsview.h"

OrderDetailsView::OrderDetailsView(KitchenController *controller, QWidget *parent)
    : QDialog(parent), controller(controller)
{
    // TODO: order header, items with ingredients, Mark Completed button.
}
