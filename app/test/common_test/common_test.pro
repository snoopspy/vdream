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
	../../../include/common/vbase.cpp \
	../../../include/common/vdependency.cpp \
	../../../include/common/vinstance.cpp

HEADERS += \
	../../../include/etc/vmyobject.h
