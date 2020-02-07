#-------------------------------------------------
#
# Project created by QtCreator 2019-06-17T09:58:05
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += core network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main/main.cpp \
        main/mainwindow.cpp \
        Ymodem/Ymodem.cpp \
        Ymodem/YmodemFileReceive.cpp \
        Ymodem/YmodemFileTransmit.cpp \
        convert/convert.cpp \
        serial_tool/serial_tool.cpp \
        Ymodem/ui_ymodem.cpp \
        form.cpp \
        net_tool/net_tool.cpp \
        gprs_nb_tool/gprs_nb_tool.cpp \
        Tool/Check/check.cpp \
        Tool/ascii.cpp \
#        mqtt/ui_mqtt.cpp \
        Tool/format.cpp

HEADERS += \
        main/mainwindow.h \
        Ymodem/Ymodem.h \
        Ymodem/YmodemFileReceive.h \
        Ymodem/YmodemFileTransmit.h \
        convert/convert.h \
        serial_tool/serial_tool.h \
        Ymodem/ui_ymodem.h \
        form.h \
        net_tool/net_tool.h \
        gprs_nb_tool/gprs_nb_tool.h \
        Tool/Check/check.h \
        Tool/ascii.h \
#        mqtt/ui_mqtt.h \
        Tool/format.h

FORMS += \
        main/mainwindow.ui \
        serial_tool/serial_tool.ui \
        Ymodem/ui_ymodem.ui \
        form.ui \
        net_tool/net_tool.ui \
        gprs_nb_tool/gprs_nb_tool.ui \
        Tool/Check/check.ui \
#        Tool/ascii.ui \
        mqtt/ui_mqtt.ui \
        Tool/format.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RC_ICONS = img/logo.ico

RESOURCES += \
    img.qrc


INCLUDEPATH += main
INCLUDEPATH += Ymodem
INCLUDEPATH += convert
INCLUDEPATH += serial_tool


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lQt5Mqtt
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lQt5Mqttd

#INCLUDEPATH += $$PWD/include
#DEPENDPATH += $$PWD/include


