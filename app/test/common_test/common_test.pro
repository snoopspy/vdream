QT += core
QT -= gui

include (../../../../../etc/gtest/gtest.pri)
include (../../../lib/vdream.pri)

TARGET = common_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    test1.cpp \
	../../../include/common/vbase.cpp \
	../../../include/common/vdebugnew.cpp \
	../../../include/common/vdependency.cpp \
	../../../include/common/vmemoryleak.cpp \
	../../../include/common/vinstance.cpp \
	../../../include/common/vthread.cpp \
	../../../include/common/vapp.cpp

HEADERS += \
	../../../include/common/vbase.h \
	../../../include/common/vdebugnew.h \
	../../../include/common/vdependency.h \
	../../../include/common/vmemoryleak.h \
	../../../include/common/vinstance.h \
	../../../include/common/vthread.h \
	../../../include/common/vapp.h
