/*
 * DefaultDataLoader -- implementation
 *
 * TODO:
 *   - Build objects from the tables below and add them through
 *     DataStorage: ingredients, then the menu, then users with their past
 *     orders. [D1 p.1-2 Default System Data]
 *   - Once Order and Customer have their rules, replay each history from
 *     zero and check it lands on the balances listed here. [D1 p.2 Default
 *     System Data]
 *   - Points earned assume "$3 paid" means the amount charged, so account
 *     credit doesn't earn points. Confirm on the forum. [Overview sec. 3]
 */

#include "defaultdataloader.h"

#include <QList>
#include <QHash>

#include "datastorage.h"
#include "systemadministrator.h"
#include "kitchenstaff.h"
#include "manager.h"
#include "cashier.h"
#include "customer.h"
#include "ingredient.h"
#include "menuitem.h"
#include "recipeingredient.h"
#include "order.h"
#include "orderitem.h"
#include <QDateTime>

namespace {

struct IngredientData
{
    const char *name;
    const char *unit;
};

struct RecipeLineData
{
    const char *ingredient;
    int quantity;
};

struct MenuItemData
{
    const char *name;
    const char *category;
    int priceCents;
    QList<RecipeLineData> recipe;
};

struct StaffData
{
    const char *role;
    const char *name;
    const char *username;
    const char *staffId;
};

struct OrderLineData
{
    const char *menuItem;
    int quantity;
};

struct PastOrderData
{
    int number;
    const char *placedAt;   // YYYY-MM-DD:HH:MM
    const char *type;       // "Online" or "In Person"
    const char *status;     // "Picked Up" or "Cancelled"
    QList<OrderLineData> items;
    int pointsUsed;
    int creditUsedCents;
    int finalPriceCents;    // subtotal + 15% tax
    int amountChargedCents;
    int pointsEarned;       // 0 when cancelled: earned points are taken back
};

struct CustomerData
{
    const char *name;
    const char *username;
    const char *loyaltyNumber;
    const char *email;
    const char *homeAddress;
    int pointsBalance;
    int creditCents;
    QList<PastOrderData> history;
};

// Units are what one serving uses.
const QList<IngredientData> defaultIngredients = {
    {"Bread", "slices"},
    {"Cheddar", "g"},
    {"Butter", "g"},
    {"Chicken", "g"},
    {"Bacon", "strips"},
    {"Lettuce", "g"},
    {"Tomato", "slices"},
    {"Mayonnaise", "g"},
    {"Pesto", "g"},
    {"Espresso", "shots"},
    {"Milk", "ml"},
    {"Chocolate syrup", "ml"},
    {"Chai concentrate", "ml"},
    {"Green tea", "bags"},
    {"Honey", "g"},
    {"Hot water", "ml"},
    {"Cold brew", "ml"},
    {"Ice", "g"},
    {"Lemon juice", "ml"},
    {"Sugar syrup", "ml"},
    {"Water", "ml"},
    {"Mixed berries", "g"},
    {"Yogurt", "g"},
};

// Prices are in cents and are multiples of $0.20, so 15% tax always comes out to whole cents.
const QList<MenuItemData> defaultMenu = {
    {"Kingsroad Club", "Sandwich", 1240,
     {{"Bread", 3}, {"Chicken", 80}, {"Bacon", 2}, {"Lettuce", 15}, {"Tomato", 2}, {"Mayonnaise", 15}}},
    {"Hot Pie Grilled Cheese", "Sandwich", 860,
     {{"Bread", 2}, {"Cheddar", 60}, {"Butter", 10}}},
    {"Wolfswood BLT", "Sandwich", 1020,
     {{"Bread", 2}, {"Bacon", 4}, {"Lettuce", 20}, {"Tomato", 2}, {"Mayonnaise", 10}}},
    {"Chicken Pesto Melt", "Sandwich", 1180,
     {{"Bread", 2}, {"Chicken", 100}, {"Cheddar", 40}, {"Pesto", 20}, {"Butter", 10}}},
    {"Long Night Americano", "Hot Beverage", 360,
     {{"Espresso", 2}, {"Hot water", 200}}},
    {"Old Nan's Chai Latte", "Hot Beverage", 520,
     {{"Chai concentrate", 120}, {"Milk", 180}}},
    {"Honey Green Tea", "Hot Beverage", 320,
     {{"Green tea", 1}, {"Hot water", 300}, {"Honey", 10}}},
    {"Dragonglass Mocha", "Hot Beverage", 580,
     {{"Espresso", 2}, {"Milk", 220}, {"Chocolate syrup", 30}}},
    {"Frostfang Cold Brew", "Cold Beverage", 480,
     {{"Cold brew", 300}, {"Ice", 100}}},
    {"Sunspear Lemonade", "Cold Beverage", 420,
     {{"Lemon juice", 60}, {"Sugar syrup", 30}, {"Water", 250}, {"Ice", 100}}},
    {"Berry Smoothie", "Cold Beverage", 640,
     {{"Mixed berries", 150}, {"Yogurt", 120}, {"Milk", 100}, {"Honey", 15}}},
};

const QList<StaffData> defaultStaff = {
    {"Kitchen Staff", "Timmy Tortoise", "ttortoise", "STF-001"},
    {"Kitchen Staff", "Gerald Waters", "gwaters", "STF-002"},
    {"Cashier", "Harold the Hare", "hhare", "STF-003"},
    {"Cashier", "Rosie Hill", "rhill", "STF-004"},
    {"Manager", "Walter Manderley", "wmanderley", "STF-005"},
    {"System Administrator", "Ellis Luwin", "eluwin", "STF-006"},
};

// Balances start at 0 when the account is created; the numbers below are what
// each customer's five past orders add up to (oldest first).
// Order columns: number, placed at, type, status, items, points used, credit used,
// final price, amount charged, points earned. Money is in cents.
const QList<CustomerData> defaultCustomers = {
    {"Samuel Tarley", "starley", "DE-10001", "samuel.tarley@ravenmail.com",
     "14 Hornhill Road, Hintonville", 16, 448,
     {
         {1002, "2026-09-03:08:12", "In Person", "Picked Up",
          {{"Kingsroad Club", 2}, {"Dragonglass Mocha", 1}},
          0, 0, 3519, 3519, 11},
         {1007, "2026-09-14:12:40", "Online", "Picked Up",
          {{"Hot Pie Grilled Cheese", 1}, {"Old Nan's Chai Latte", 1}},
          0, 0, 1587, 1587, 5},
         {1012, "2026-09-26:10:05", "Online", "Cancelled",
          {{"Chicken Pesto Melt", 1}},
          0, 0, 1357, 1357, 0},
         {1017, "2026-10-08:15:22", "Online", "Cancelled",
          {{"Kingsroad Club", 1}, {"Frostfang Cold Brew", 1}},
          8, 500, 1978, 678, 0},
         {1022, "2026-10-21:09:47", "In Person", "Picked Up",
          {{"Wolfswood BLT", 1}, {"Long Night Americano", 1}},
          0, 1587, 1587, 0, 0},
     }},
    {"Mira Reed", "mreed", "DE-10002", "mira.reed@ravenmail.com",
     "9 Greywater Lane, Hintonville", 6, 1265,
     {
         {1003, "2026-09-05:07:55", "Online", "Picked Up",
          {{"Berry Smoothie", 1}, {"Chicken Pesto Melt", 1}},
          0, 0, 2093, 2093, 6},
         {1008, "2026-09-17:13:10", "In Person", "Picked Up",
          {{"Honey Green Tea", 2}},
          0, 0, 736, 736, 2},
         {1013, "2026-09-30:11:30", "Online", "Picked Up",
          {{"Kingsroad Club", 1}},
          6, 0, 1426, 826, 0},
         {1018, "2026-10-12:08:44", "In Person", "Picked Up",
          {{"Hot Pie Grilled Cheese", 1}, {"Sunspear Lemonade", 1}},
          0, 0, 1472, 1472, 4},
         {1023, "2026-10-27:16:05", "Online", "Cancelled",
          {{"Dragonglass Mocha", 1}, {"Old Nan's Chai Latte", 1}},
          0, 0, 1265, 1265, 0},
     }},
    {"David Seaworth", "dseaworth", "DE-10003", "david.seaworth@ravenmail.com",
     "2 Blackwater Bay Road, Hintonville", 9, 0,
     {
         {1001, "2026-09-02:09:20", "In Person", "Picked Up",
          {{"Wolfswood BLT", 1}, {"Frostfang Cold Brew", 1}},
          0, 0, 1725, 1725, 5},
         {1006, "2026-09-11:07:35", "In Person", "Picked Up",
          {{"Long Night Americano", 1}},
          0, 0, 414, 414, 1},
         {1011, "2026-09-23:12:15", "In Person", "Picked Up",
          {{"Chicken Pesto Melt", 1}, {"Long Night Americano", 1}},
          0, 0, 1771, 1771, 5},
         {1016, "2026-10-06:10:50", "In Person", "Picked Up",
          {{"Hot Pie Grilled Cheese", 2}},
          8, 0, 1978, 1178, 0},
         {1021, "2026-10-19:14:30", "Online", "Picked Up",
          {{"Kingsroad Club", 1}, {"Sunspear Lemonade", 1}},
          0, 0, 1909, 1909, 6},
     }},
    {"Peter Payne", "ppayne", "DE-10004", "peter.payne@ravenmail.com",
     "31 Kingsroad, Hintonville", 0, 2105,
     {
         {1004, "2026-09-08:11:05", "Online", "Picked Up",
          {{"Old Nan's Chai Latte", 1}, {"Hot Pie Grilled Cheese", 1}},
          0, 0, 1587, 1587, 5},
         {1009, "2026-09-19:15:45", "Online", "Cancelled",
          {{"Kingsroad Club", 2}},
          0, 0, 2852, 2852, 0},
         {1014, "2026-10-01:08:20", "Online", "Picked Up",
          {{"Dragonglass Mocha", 1}},
          0, 667, 667, 0, 0},
         {1019, "2026-10-15:12:55", "Online", "Cancelled",
          {{"Berry Smoothie", 1}, {"Chicken Pesto Melt", 1}},
          5, 1000, 2093, 593, 0},
         {1024, "2026-10-29:09:10", "In Person", "Picked Up",
          {{"Wolfswood BLT", 1}},
          5, 673, 1173, 0, 0},
     }},
    {"Leanne Mormont", "lmormont", "DE-10005", "leanne.mormont@ravenmail.com",
     "5 Bear Isle Crescent, Hintonville", 8, 0,
     {
         {1005, "2026-09-09:10:25", "In Person", "Picked Up",
          {{"Frostfang Cold Brew", 1}, {"Kingsroad Club", 1}},
          0, 0, 1978, 1978, 6},
         {1010, "2026-09-21:14:05", "In Person", "Picked Up",
          {{"Sunspear Lemonade", 1}},
          0, 0, 483, 483, 1},
         {1015, "2026-10-03:13:35", "Online", "Picked Up",
          {{"Berry Smoothie", 2}},
          0, 0, 1472, 1472, 4},
         {1020, "2026-10-17:07:50", "Online", "Picked Up",
          {{"Chicken Pesto Melt", 1}, {"Honey Green Tea", 1}},
          7, 0, 1725, 1025, 0},
         {1025, "2026-10-30:11:40", "In Person", "Picked Up",
          {{"Hot Pie Grilled Cheese", 1}, {"Long Night Americano", 1}},
          0, 0, 1403, 1403, 4},
     }},
};
User *makeStaff(const StaffData &d)
{
  const QString role = d.role;
  if (role == "Kitchen Staff")
    return new KitchenStaff(d.name, d.username, d.staffId);
  if (role == "Cashier")
    return new Cashier(d.name, d.username, d.staffId);
  if (role == "Manager")
    return new Manager(d.name, d.username, d.staffId);
  if (role == "System Administrator")
    return new SystemAdministrator(d.name, d.username, d.staffId);

  Q_ASSERT_X(false, "makeStaff", "unknown role in defaultStaff");
  return nullptr;
}
} // namespace

DefaultDataLoader::DefaultDataLoader(DataStorage &storage)
    : storage(storage)
{
}

void DefaultDataLoader::load()
{
    QHash<QString, Ingredient*> ingredientMap;
    for (const IngredientData &data : defaultIngredients){
        Ingredient *ingredient = new Ingredient(data.name, 0);
        storage.addIngredient(ingredient);
        ingredientMap.insert(data.name, ingredient);
    }

    for (const MenuItemData &data:defaultMenu){
        MenuItem *item = new MenuItem(data.name, data.category, data.priceCents);

        for(const RecipeLineData &line : data.recipe){
            Ingredient *ingredient = ingredientMap.value(line.ingredient, nullptr);

        if (ingredient!= nullptr){
            item->addIngredient(RecipeIngredient(ingredient, line.quantity));
        }
        }

        storage.addMenuItem(item);
    }
    for (const StaffData &staff : defaultStaff){
        storage.addUser(makeStaff(staff));
    }

    for (const CustomerData &data : defaultCustomers){
        Customer *customer = new Customer(
                    data.name,
                    data.username,
                    data.email,
                    data.pointsBalance)
    ;

    customer->setCreditCents(data.creditCents);
    customer->setLoyaltyNumber(data.loyaltyNumber);
    customer->setHomeAddress(data.homeAddress);

    for(const PastOrderData &past :data.history){
        Order order(past.number);
        QString dateString = QString::fromUtf8(past.placedAt);
        QDateTime date = QDateTime::fromString(
                    dateString, "yyyy-MM-dd:HH:mm");
        order.setPlacedAt(date);
        order.setStatus(past.status);
        order.setOrderType(past.type);
        order.setPayment(
                    past.pointsUsed,
                    past.creditUsedCents,
                    past.amountChargedCents,
                    past.pointsEarned
                    );
    for (const OrderLineData &line :past.items){
        for (MenuItem *item : storage.menuItems()){
            if(item->name()==line.menuItem){
                order.addItem(OrderItem(item, line.quantity));
                break;
            }
        }
    }
    customer->addOrder(order);

    }
    storage.addUser(customer);
 }
}
