/*
 * KitchenController -- Controller subsystem (control class)
 *
 * The kitchen side: the queue, order details and completing orders. Serves
 * OrderQueueView and OrderDetailsView.
 *
 * Spec notes:
 *   - Kitchen staff see every order waiting to be prepared, first-in, first-
 *     out. [Overview sec. 2, Staff: Kitchen and Order Queue Process]
 *   - Completing an order changes it from In Progress to Completed and
 *     removes it from the queue. [Overview sec. 2, Order Queue Process]
 *   - Only the In Progress to Completed transition is used in D1. [D1 p.3-4
 *     Business Rules]
 *   - Earned loyalty points are credited when the order reaches Completed.
 *     [Overview sec. 3]
 */

#ifndef KITCHENCONTROLLER_H
#define KITCHENCONTROLLER_H

class CafeDataStore;

class KitchenController
{
public:
    KitchenController();

    // TODO: operations for the views. Pass the logged-in username in
    //       (MainWindow gets it from AccountController) and return plain
    //       data (QString, numbers), not model pointers.

private:
    CafeDataStore &store;   // Figure 1: KitchenController -> CafeDataStore
};

#endif // KITCHENCONTROLLER_H
