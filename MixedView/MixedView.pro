#-------------------------------------------------
#
# Project created by QtCreator 2010-10-15T08:28:58
#
#-------------------------------------------------

QT       += core gui multimedia network

TARGET = MixedView
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH+=../../../src/network ../../../src/sensors ../../src/multimedia ../../src/multimedia/audio


CONFIG += mobility
MOBILITY += contacts messaging systeminfo sensors multimedia

symbian {
    TARGET.UID3 = 0xe4cef592
    LIBS += -lcone -leikcore -lavkon
    TARGET.CAPABILITY += AllFiles LocalServices ReadUserData WriteUserData NetworkServices UserEnvironment Location ReadDeviceData
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x10000000
}

RESOURCES += resources.qrc
