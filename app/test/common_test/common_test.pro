QT += core
QT -= gui

include(../../../vdream.pri)
include(../../../../../google/gtest/gtest.pri)

TARGET    = common_test
CONFIG   += console
CONFIG   -= app_bundle
DESTDIR   = $${PWD}/../../../bin
TEMPLATE = app

SOURCES += \
  ../../../src/etc/vmyobject.cpp

HEADERS += \
  ../../../src/etc/vmyobject.h
