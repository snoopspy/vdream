QT += core xml

#------------------------------------------------------------------------------
# debug and release
#------------------------------------------------------------------------------
CONFIG(debug, debug|release)   DEFINES += _DEBUG
CONFIG(release, debug|release) DEFINES += _RELEASE

#------------------------------------------------------------------------------
# library name
#------------------------------------------------------------------------------
VDREAM_LIB_NAME = vdream
android-g++:                 VDREAM_LIB_NAME = $${VDREAM_LIB_NAME}_android
contains(QT, gui)            VDREAM_LIB_NAME = $${VDREAM_LIB_NAME}_gui
CONFIG(GTEST)                VDREAM_LIB_NAME = $${VDREAM_LIB_NAME}_test
CONFIG(debug, debug|release) VDREAM_LIB_NAME = $${VDREAM_LIB_NAME}_d
message($${VDREAM_LIB_NAME}) # gilgil temp 2015.01.20

#------------------------------------------------------------------------------
# vdream
#------------------------------------------------------------------------------
VDREAM_DIR = $${PWD}
INCLUDEPATH += $${VDREAM_DIR}/src
!CONFIG(VDREAM_LIB_BUILD) {
	PRE_TARGETDEPS +=  $${VDREAM_DIR}/lib/lib$${VDREAM_LIB_NAME}.a
	LIBS           += -L$${VDREAM_DIR}/lib -l$${VDREAM_LIB_NAME}
	LIBS           += -l$${VDREAM_LIB_NAME}
}
mingw: DEFINES += __USE_MINGW_ANSI_STDIO=1 # gilgil temp 2015.02.24

#------------------------------------------------------------------------------
# winsock
#------------------------------------------------------------------------------
win32: LIBS += -lws2_32

#------------------------------------------------------------------------------
# openssl
#------------------------------------------------------------------------------
win32 {
	contains(QMAKE_TARGET.arch, x86_64) {
		OPENSSL_DIR = C:/OpenSSL-Win64
	} else {
		OPENSSL_DIR = C:/OpenSSL-Win32
	}
	INCLUDEPATH += $${OPENSSL_DIR}/include
	LIBS        += -L$${OPENSSL_DIR}/lib
	LIBS        += -llibeay32 -lssleay32
}
linux: LIBS += -lssl -lcrypto
