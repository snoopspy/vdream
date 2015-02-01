QT += core
QT -= gui

include(../../../../../google/gtest/gtest.pri)
include(../../../lib/vdream.pri)

TARGET    = common_test
CONFIG   += console
CONFIG   -= app_bundle
DESTDIR   = $${PWD}/../../../bin

TEMPLATE = app

SOURCES += \
  ../../../src/etc/vmyobject.cpp

HEADERS += \
  ../../../src/etc/vmyobject.h
