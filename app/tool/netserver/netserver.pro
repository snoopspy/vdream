#-------------------------------------------------
#
# Project created by QtCreator 2014-02-27T14:42:11
#
#-------------------------------------------------

QT += core gui widgets

include(../../../vdream.pri)

TARGET   = netserver
TEMPLATE = app
DESTDIR   = $${PWD}/../../../bin

SOURCES += main.cpp \
    widget.cpp

HEADERS  += \
    widget.h

FORMS    += \
    widget.ui
