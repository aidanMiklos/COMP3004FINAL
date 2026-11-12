#include <QCoreApplication>
#include <QDebug>
#include "user.h"
#include "customer.h"
#include "recipeingredient.h"
#include "menuitem.h"
#include "orderitem.h"
#include "order.h"
#include "orderqueue.h"
#include "cashier.h"
#include "manager.h"
#include "systemadministrator.h"
#include "datastorage.h"
#include "inmemorystorage.h"
#include "cafedatastore.h"
#include "defaultdataloader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //User user(11, "tony");
    Customer customer("tony", "Tony123", "tony@test.com", 22);
    qDebug()<< "the name is:" << customer.name();
    qDebug()<< "the user name is:" << customer.username();
    qDebug()<< "the role is:" << customer.roleName();
    qDebug()<< "the email is:" << customer.email();
    qDebug()<< "the points had was:" << customer.loyaltyPoints();

    customer.addLoyaltyPoints(10);
    qDebug()<< "the points after is:" << customer.loyaltyPoints();

    Ingredient milk("Milk", 20);
    RecipeIngredient latteMilk(&milk, 2);

    qDebug() << latteMilk.ingredient()-> name();
    qDebug() << latteMilk.quantity();

    MenuItem latte("Latte", 450);
    qDebug() << latte.name();
    qDebug() << latte.priceCents();
    qDebug() << latte.avaliable();

    OrderItem item(&latte, 2);
    qDebug() << item.menuItem()->name();
    qDebug() << item.quantity();
    qDebug() << item.subtotalCents();

    Order order(1001);
    order.addItem(item);
    qDebug() << order.subtotalCents();
    qDebug() << order.taxCents();
    qDebug() << order.totalCents();

    OrderQueue queue;
    queue.addOrder(&order);
    qDebug()<<queue.size();
    queue.removeOrder(1001);
    qDebug()<<queue.size();


    Cashier cashier("John", "John001", "cash01");
    qDebug() << cashier.name();
    qDebug() << cashier.staffId();
    qDebug() << cashier.roleName();

    Manager manager("amy", "amy001", "manag01");
    qDebug() << manager.name();
    qDebug() << manager.staffId();
    qDebug() << manager.roleName();

    SystemAdministrator systemAdministrator("jack", "jack001", "admin01");
    qDebug() << systemAdministrator.name();
    qDebug() << systemAdministrator.staffId();
    qDebug() << systemAdministrator.roleName();

    InMemoryStorage memory;
    DataStorage *storage = &memory;
    storage->addMenuItem(new MenuItem("Latte", 140));
    qDebug() << storage->menuItems().first()->name();
    qDebug() << storage->menuItems().first()->priceCents();

    CafeDataStore &store1 = CafeDataStore::instance();
    CafeDataStore &store2 = CafeDataStore::instance();
    qDebug() << (&store1 == &store2);

    qDebug() << "Default menu items:"
             << store1.menuItems().size();

    qDebug() << store1.findUser("ttortoise")->roleName();
    qDebug() << store2.findUser("starley")->roleName();
    qDebug() << store1.menuItems().first()-> ingredients().size();

    order.setStatus("Picked up");
    order.setOrderType("IN person");
    order.setPayment(5, 200, 100, 3);
    qDebug() << order.status()
             << order.orderType()
             << order.pointsUsed();

    customer.setCreditCents(500);
    customer.addOrder(order);
    qDebug() << customer.creditCents()
             << customer.orderHistory().size();

    Customer *c = dynamic_cast<Customer*>(store1.findUser("starley"));
    //qDebug() << c->orderHistory().size();
    //qDebug() << c->creditCents();

    /*if (c){
        qDebug() << c->loyaltyNumber();
        qDebug() << c->homeAddress();
    }*/

    /*if (c != nullptr){
        qDebug() << "Customer:" << c->name();
        qDebug()<< "History count:" << c->orderHistory().size();

        for (const Order &past : c->orderHistory()){
            qDebug()<< "order:" << past.orderId()
                    << "valid:" << past.placedAt().isValid()
                    <<" Date:" << past.placedAt().toString("yyyy-MM-dd HH:mm");
        }*/
    Order  onlineOrder(2001);
    onlineOrder.addItem(OrderItem(store1.menuItems().first(), 2));

    qDebug() << onlineOrder.subtotalCents();
    qDebug() << onlineOrder.taxCents();
    qDebug() << onlineOrder.totalCents();

    if (c != nullptr){
        c->addOrder(onlineOrder);
        qDebug() << "History count:" << c->orderHistory().size();
        qDebug()<< "last order:" << c->orderHistory().last().orderId();

    OrderQueue &kitchen = store1.orderQueue();
    kitchen.addOrder(&onlineOrder);
    qDebug() << "Kitchen queue size:" << kitchen.size();
    kitchen.removeOrder(2001);
    qDebug() << "Kitchen queue size:" << kitchen.size();
    onlineOrder.setStatus("Completed");
    qDebug() << "Order ID:" <<onlineOrder.orderId();
    qDebug() << "Order status:" <<onlineOrder.status();


    return 0;


}
}
