
QT       += core gui sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MainWindow.cpp \
    deal.cpp \
    edit_infor.cpp \
    main.cpp \
    passenger.cpp \
    sign_in.cpp \
    single_center.cpp \
    order_dialog.cpp \
    userprofile.cpp

HEADERS += \
    MainWindow.h \
    deal.h \
    passenger.h \
    edit_infor.h \
    sign_in.h \
    single_center.h \
    order_dialog.h \
    userprofile.h

FORMS += \
    MainWindow.ui \
    deal.ui \
    passenger.ui \
    edit_infor.ui \
    sign_in.ui \
    single_center.ui \
    order_dialog.ui \
    userprofile.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target