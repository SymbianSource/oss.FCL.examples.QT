#-------------------------------------------------
#
# Project created by QtCreator 2010-10-06T10:31:49
#
#-------------------------------------------------

QT       += core gui webkit

TARGET = mywebwidget3
TEMPLATE = app


SOURCES += main.cpp\
        mywebwidget.cpp \
    mytoolbar.cpp

HEADERS  += mywebwidget.h \
    mytoolbar.h

CONFIG += mobility
MOBILITY = location

symbian {
    TARGET.UID3 = 0xe1b774b2
    TARGET.CAPABILITY += LocalServices ReadUserData WriteUserData NetworkServices UserEnvironment Location
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x4000000
}
