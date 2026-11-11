# DragonEndPOS.pro -- qmake project file
#
# Spec notes:
#   - Build with qmake, not CMake; this file lists every .cpp, .h and .ui
#     file. [D1 p.4 Submission Requirements]
#   - No hardcoded absolute paths ($$PWD is relative to this file).
#     [D1 p.5 Submission Requirements]
#   - C++ with Qt Creator 6.0.2 on the course VM, using only libraries
#     already on the VM. [D1 p.4 Implementation Requirements]

QT += core gui widgets
CONFIG += c++17
TEMPLATE = app
TARGET = DragonEndPOS

# One folder per subsystem in Figure 1.
INCLUDEPATH += \
    $$PWD/src/model \
    $$PWD/src/controller \
    $$PWD/src/view

SOURCES += \
    src/main.cpp \
    src/model/cafedatastore.cpp \
    src/model/cashier.cpp \
    src/model/customer.cpp \
    src/model/defaultdataloader.cpp \
    src/model/ingredient.cpp \
    src/model/inmemorystorage.cpp \
    src/model/kitchenstaff.cpp \
    src/model/manager.cpp \
    src/model/menuitem.cpp \
    src/model/order.cpp \
    src/model/orderitem.cpp \
    src/model/orderqueue.cpp \
    src/model/recipeingredient.cpp \
    src/model/staff.cpp \
    src/model/systemadministrator.cpp \
    src/model/user.cpp \
    src/controller/accountcontroller.cpp \
    src/controller/dashboardcontroller.cpp \
    src/controller/kitchencontroller.cpp \
    src/controller/menucontroller.cpp \
    src/controller/ordercontroller.cpp \
    src/view/dashboardview.cpp \
    src/view/loginview.cpp \
    src/view/mainwindow.cpp \
    src/view/makeorderview.cpp \
    src/view/menuview.cpp \
    src/view/orderdetailsview.cpp \
    src/view/orderqueueview.cpp

HEADERS += \
    src/model/cafedatastore.h \
    src/model/cashier.h \
    src/model/customer.h \
    src/model/datastorage.h \
    src/model/defaultdataloader.h \
    src/model/ingredient.h \
    src/model/inmemorystorage.h \
    src/model/kitchenstaff.h \
    src/model/manager.h \
    src/model/menuitem.h \
    src/model/order.h \
    src/model/orderitem.h \
    src/model/orderqueue.h \
    src/model/recipeingredient.h \
    src/model/staff.h \
    src/model/systemadministrator.h \
    src/model/user.h \
    src/controller/accountcontroller.h \
    src/controller/dashboardcontroller.h \
    src/controller/kitchencontroller.h \
    src/controller/menucontroller.h \
    src/controller/ordercontroller.h \
    src/view/dashboardview.h \
    src/view/loginview.h \
    src/view/mainwindow.h \
    src/view/makeorderview.h \
    src/view/menuview.h \
    src/view/orderdetailsview.h \
    src/view/orderqueueview.h
