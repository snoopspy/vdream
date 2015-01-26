#-------------------------------------------------
#
# Project created by QtCreator 2013-01-16T10:37:14
#
#-------------------------------------------------

QT -= gui

include(../../../lib/vdream.pri)

TARGET    = nets
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE  = app
DESTDIR   = $${PWD}/../../../bin

SOURCES += \
    main.cpp \
    param.cpp

HEADERS += \
    param.h \
    main.h
