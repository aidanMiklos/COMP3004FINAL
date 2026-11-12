QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        cafedatastore.cpp \
        cashier.cpp \
        customer.cpp \
        defaultdataloader.cpp \
        ingredient.cpp \
        inmemorystorage.cpp \
        kitchenstaff.cpp \
        main.cpp \
        manager.cpp \
        menuitem.cpp \
        order.cpp \
        orderitem.cpp \
        orderqueue.cpp \
        recipeingredient.cpp \
        staff.cpp \
        systemadministrator.cpp \
        user.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cafedatastore.h \
    cashier.h \
    customer.h \
    datastorage.h \
    defaultdataloader.h \
    ingredient.h \
    inmemorystorage.h \
    kitchenstaff.h \
    manager.h \
    menuitem.h \
    order.h \
    orderitem.h \
    orderqueue.h \
    recipeingredient.h \
    staff.h \
    systemadministrator.h \
    user.h
