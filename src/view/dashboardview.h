/*
 * DashboardView -- View subsystem (boundary class)
 *
 * The customer's dashboard page: account details, the current order and the
 * order history.
 *
 * Spec notes:
 *   - Show the loyalty points number, points balance, account credit, name,
 *     email address and home address. [Overview sec. 2, Online Dashboard]
 *   - The Overview also lets customers update their email and home address,
 *     and D1 points to that section, so decide whether to include it.
 *     [Overview sec. 2, Online Dashboard; D1 p.2 Functional Requirements]
 *   - Show the current order (In Progress or Completed): order number,
 *     items, final price with tax, points used or earned, credit used,
 *     status. [D1 p.3 Feature 4; Overview sec. 2, Online Dashboard]
 *   - Show the last 5 orders (Picked Up or Cancelled only): order number,
 *     items, final price with tax, points used or earned, credit used or
 *     received, status, and online or in person. [Overview sec. 2, Online
 *     Dashboard]
 *   - Orders placed during this run stay as the current order and never move
 *     into the history. [D1 p.3 Feature 4]
 */

#ifndef DASHBOARDVIEW_H
#define DASHBOARDVIEW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class DashboardView; }
QT_END_NAMESPACE

class DashboardController;

class DashboardView : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardView(DashboardController *controller, QWidget *parent = nullptr);

// Used to notify the controller of stuff that has occurred
signals:

    // viewShown is a signal all widgets have, so all views will have one as well.
    void viewShown();

// Used to receive signals from the controller
public slots:
    void displayUsername(const QString &name);


private:
    DashboardController *controller;   // Figure 1: DashboardView -> DashboardController

    Ui::DashboardView *ui;
};

#endif // DASHBOARDVIEW_H
