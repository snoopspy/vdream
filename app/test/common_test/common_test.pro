QT += core
QT -= gui

include (../../../../../google/gtest/gtest.pri)
include (../../../lib/vdream.pri)

TARGET = common_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    test1.cpp \
  ../../../include/base/vbase.cpp \
  ../../../include/base/vdebugnew.cpp \
  ../../../include/base/vdependency.cpp \
  ../../../include/base/vmemoryleak.cpp \
  ../../../include/base/vinstance.cpp \
  ../../../include/base/vthread.cpp \
  ../../../include/base/vapp.cpp

HEADERS += \
  ../../../include/base/vbase.h \
  ../../../include/base/vdebugnew.h \
  ../../../include/base/vdependency.h \
  ../../../include/base/vmemoryleak.h \
  ../../../include/base/vinstance.h \
  ../../../include/base/vthread.h \
  ../../../include/base/vapp.h
