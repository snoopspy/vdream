QT += core
QT -= gui

include (../../../../../google/gtest/gtest.pri)
include (../../../lib/vdream.pri)

TARGET    = common_test
CONFIG   += console
CONFIG   -= app_bundle
DESTDIR   = $${PWD}/../../../bin

TEMPLATE = app

SOURCES += \
    test1.cpp \
  ../../../src/base/vbase.cpp \
  ../../../src/base/vdebugnew.cpp \
  ../../../src/base/vdependency.cpp \
  ../../../src/base/vmemoryleak.cpp \
  ../../../src/base/vinstance.cpp \
  ../../../src/base/vthread.cpp \
  ../../../src/base/vapp.cpp

HEADERS += \
  ../../../src/base/vbase.h \
  ../../../src/base/vdebugnew.h \
  ../../../src/base/vdependency.h \
  ../../../src/base/vmemoryleak.h \
  ../../../src/base/vinstance.h \
  ../../../src/base/vthread.h \
  ../../../src/base/vapp.h
