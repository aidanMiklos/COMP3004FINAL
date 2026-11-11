# DragonEndPOS: Deliverable 1

COMP 3004 Fall 2026 
Team 57 
Aidan Miklos, Kishaan Gidda, Henri Linkletter, Yiuxuan Han

In-memory prototype of the Dragon's End Café Point of Sales System. Customers view the menu, place an online order and view their dashboard; kitchen staff view the order queue and complete orders. Written in C++ with Qt Widgets, built with qmake, and organised as Model-View-Controller (docs/D1-system-decomposition.pdf).

## Setup, build and launch

Requires the course VM (Ubuntu) with Qt Creator 6.0.2 and the Qt version it ships with. No other libraries.

**Qt Creator**

1. Extract `team_57_D1.zip`.
2. Open `DragonEndPOS.pro` in Qt Creator (File > Open File or Project).
3. Keep the default kit and click **Configure Project**.
4. Build (Ctrl+B), then Run (Ctrl+R).

**Terminal**

```bash
mkdir build && cd build
qmake ../DragonEndPOS.pro
make
./DragonEndPOS
```

## Test users

TODO: list all 11 default users.

| Role | Name | Username |
|---|---|---|
| Customer | TODO | TODO |
| Customer | TODO | TODO |
| Customer | TODO | TODO |
| Customer | TODO | TODO |
| Customer | TODO | TODO |
| Kitchen Staff | TODO | TODO |
| Kitchen Staff | TODO | TODO |
| Cashier | TODO | TODO |
| Cashier | TODO | TODO |
| Manager | TODO | TODO |
| System Administrator | TODO | TODO |

## Not implemented or partly implemented

Nothing so far has been implemented.

## Files

Each source file opens with a comment listing the spec requirements it covers, with the page (`D1` = `D1-Outline.pdf`) or section (`Overview` = the Project Overview) they come from. Most classes have a `.h` and a `.cpp`.

```
DragonEndPOS.pro              qmake project: Qt modules, include paths, every source file
src/main.cpp                  Creates the controllers and MainWindow, starts the app

src/view/                     View subsystem (Qt widgets)
  mainwindow                  The one window: page stack, role header, role menus, Log out
  loginview                   Startup form: enter a name or username
  menuview                    Menu grouped by category (also embedded in makeorderview)
  makeorderview               Pick items, apply points/credit, price breakdown, submit
  dashboardview               Customer account details, current order, last 5 orders
  orderqueueview              Kitchen queue: number, customer, date/time, oldest first
  orderdetailsview            Dialog: items with ingredients, Mark Completed

src/controller/               Controller subsystem
  accountcontroller           Identify the user, remember who is logged in, log out
  menucontroller              Menu items grouped by category
  ordercontroller             Draft order, price breakdown, one-order rule, submit
  kitchencontroller           Queue, order details, complete an order
  dashboardcontroller         Data for the customer dashboard

src/model/                    Model subsystem
  cafedatastore               Singleton facade: the only Model class controllers use
  datastorage                 Abstract storage interface (Bridge), header only
  inmemorystorage             D1 storage: keeps every object in memory
  defaultdataloader           Loads the default menu, users and order histories
  user, staff                 Abstract bases for all users and for staff
  customer                    Customer account, current order, order history
  kitchenstaff, cashier,
  manager,
  systemadministrator         Staff roles
  menuitem                    Menu item and its recipe lines
  recipeingredient            One recipe line: ingredient and quantity
  ingredient                  An ingredient, shared between recipes
  order                       An order; holds the pricing and loyalty rules
  orderitem                   One order line: menu item and quantity
  orderqueue                  Kitchen queue of paid orders, oldest first

```
