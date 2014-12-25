QT += core xml

#-------------------------------------------------
# debug and release
#-------------------------------------------------
CONFIG(debug, debug|release) {
	DEFINES += _DEBUG
}
CONFIG(release, debug|release) {
	DEFINES += _RELEASE
}

#-------------------------------------------------
# library name
#-------------------------------------------------
VDREAM_LIB_NAME = vdream
CONFIG(debug, debug|release) {
	VDREAM_LIB_NAME = $${VDREAM_LIB_NAME}_d
}
contains(QT, gui) {
	VDREAM_LIB_NAME = $${VDREAM_LIB_NAME}_gui
}
android-g++ {
	VDREAM_LIB_NAME = $${VDREAM_LIB_NAME}_android
}

#-------------------------------------------------
# vdream
#-------------------------------------------------
VDREAM_PATH  = $${PWD}/..
INCLUDEPATH += $${VDREAM_PATH}/include
# DEPENDPATH  += $${VDREAM_PATH} ## gilgil temp 2014.12.02
!CONFIG(VDREAM_LIB_BUILD) {
	gcc:PRE_TARGETDEPS +=  $${VDREAM_PATH}/lib/lib$${VDREAM_LIB_NAME}.a
	LIBS               += -L$${VDREAM_PATH}/lib -l$${VDREAM_LIB_NAME}
	LIBS               += -l$${VDREAM_LIB_NAME}
}

#-------------------------------------------------
# winsock
#-------------------------------------------------
win32 {
	LIBS += -lws2_32
}

#-------------------------------------------------
# openssl
#-------------------------------------------------
win32 {
	contains(QMAKE_TARGET.arch, x86_64) {
		OPENSSL_PATH = C:/OpenSSL-Win64
	} else {
		OPENSSL_PATH = C:/OpenSSL-Win32
	}
	INCLUDEPATH += $${OPENSSL_PATH}/include
	LIBS        += -L$${OPENSSL_PATH}/lib
	LIBS        += -llibeay32 -lssleay32
}
linux {
	LIBS        += -lssl -lcrypto
}
