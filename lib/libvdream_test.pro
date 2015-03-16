QT -= gui

include(../../../google/gtest/gtest.pri)
include(libvdream.pri)

TARGET   = $${VDREAM_LIB_NAME}
TEMPLATE = lib
CONFIG  += staticlib
DESTDIR  = $${PWD}
