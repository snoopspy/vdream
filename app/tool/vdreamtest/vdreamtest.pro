#-------------------------------------------------
#
# Project created by QtCreator 2012-05-24T20:39:05
#
#-------------------------------------------------

QT -= gui

include(../../../lib/vdream.pri)

TARGET    = vdreamtest
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE  = app
DESTDIR   = $${PWD}/../../../bin

SOURCES += \
    main.cpp

HEADERS += \
    main.h
