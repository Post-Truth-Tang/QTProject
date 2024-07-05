QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TQZController/TQZMessageController.cpp \
    TQZController/TQZTradeController.cpp \
    TQZController/TestController.cpp \
    TQZController/TQZMainController.cpp \
    TQZController/IController.cpp \
    TQZModel/TQZAccountModel.cpp \
    TQZView/ITableWidget.cpp \
    TQZView/TQZBalanceView.cpp \
    TQZView/TQZBanView.cpp \
    TQZView/TQZButton.cpp \
    TQZView/TQZLabel.cpp \
    TQZView/TQZOrderTableWidget.cpp \
    TQZView/TQZPositionTableWidget.cpp \
    TQZView/TQZToolItemsView.cpp \
    TQZView/TQZTradeButtonView.cpp \
    TQZView/TQZTradeTableWidget.cpp \
    main.cpp

HEADERS += \
    TQZController/TQZMessageController.h \
    TQZController/TQZTradeController.h \
    TQZController/TestController.h \
    TQZController/TQZMainController.h \
    TQZController/IController.h \
    TQZModel/TQZAccountModel.h \
    TQZView/ITableWidget.h \
    TQZView/TQZBalanceView.h \
    TQZView/TQZBanView.h \
    TQZView/TQZButton.h \
    TQZView/TQZLabel.h \
    TQZView/TQZOrderTableWidget.h \
    TQZView/TQZPositionTableWidget.h \
    TQZView/TQZToolItemsView.h \
    TQZView/TQZTradeButtonView.h \
    TQZView/TQZTradeTableWidget.h

FORMS += \
    mainwindow.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
