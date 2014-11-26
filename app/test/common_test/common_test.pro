QT += core
QT -= gui

include (../../../lib/vdream.pri)
include (../../../../../etc/gtest/gtest.pri)

TARGET = common_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    test1.cpp \
    ../../../include/etc/vmyobj.cpp \
    ../../../include/common/vdesign.cpp

HEADERS += \
    ../../../include/etc/vmyobj.h
