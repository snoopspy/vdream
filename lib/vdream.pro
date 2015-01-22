CONFIG(VDREAM_LIB_BUILD_GUI) {
  QT += gui widgets
} else {
  QT -= gui
}

CONFIG += VDREAM_LIB_BUILD
include (vdream.pri)

TARGET   = $${VDREAM_LIB_NAME}
TEMPLATE = lib
CONFIG  += staticlib
DESTDIR  = $${PWD}

SOURCES += \
  ../include/etc/vdatafind.cpp \
  ../include/etc/vmyobject.cpp \
  ../include/etc/vlistwidget.cpp \
  ../include/etc/vint.cpp \
  ../include/etc/vdatachange.cpp \
  ../include/graph/vgraph.cpp \
  ../include/graph/vgraphnode.cpp \
  ../include/graph/vgraphlink.cpp \
  ../include/graph/vgraphstream.cpp \
  ../include/log/vloglist.cpp \
  ../include/log/vlogfile.cpp \
  ../include/log/vlognull.cpp \
  ../include/log/vlog.cpp \
  ../include/log/vlogdbwin32.cpp \
  ../include/log/vlogstderr.cpp \
  ../include/log/vlogfactory.cpp \
  ../include/log/vlogstdout.cpp \
  ../include/log/vloghttp.cpp \
  ../include/log/vlogudp.cpp \
  ../include/base/vrwobject.cpp \
  ../include/base/vxmldoc.cpp \
  ../include/base/vtick.cpp \
  ../include/base/vperformance.cpp \
  ../include/base/vexception.cpp \
  ../include/base/vthread.cpp \
  ../include/base/vsystem.cpp \
  ../include/base/vdebugnew.cpp \
  ../include/base/vobjectwidget.cpp \
  ../include/base/vapp.cpp \
  ../include/base/vmemoryleak.cpp \
  ../include/base/vmetaclass.cpp \
  ../include/base/vxml.cpp \
  ../include/base/vfile.cpp \
  ../include/base/vobject.cpp \
  ../include/base/vinstance.cpp \
  ../include/base/vdependency.cpp \
  ../include/base/verror.cpp \
  ../include/base/vprimitive.cpp \
  ../include/net/vnetclient.cpp \
  ../include/net/vnetfactory.cpp \
  ../include/net/vudpclient.cpp \
  ../include/net/vsslserver.cpp \
  ../include/net/vudpserver.cpp \
  ../include/net/vsslclient.cpp \
  ../include/net/vtcpsession.cpp \
  ../include/net/vsslsession.cpp \
  ../include/net/vudpsession.cpp \
  ../include/net/vtcpclient.cpp \
  ../include/net/vnetserver.cpp \
  ../include/net/http/vwebproxy.cpp \
  ../include/net/http/vwebproxywidget.cpp \
  ../include/net/http/vhttpchunkbody.cpp \
  ../include/net/http/vhttprequest.cpp \
  ../include/net/http/vhttpheader.cpp \
  ../include/net/http/vhttpresponse.cpp \
  ../include/net/vtcpserver.cpp \
  ../include/net/vnet.cpp \
	../include/base/vbase.cpp \
    ../include/net/vsslbase.cpp

HEADERS += \
  ../include/etc/vint.h \
  ../include/etc/vmyobject.h \
  ../include/etc/vdatachange.h \
  ../include/etc/vdatafind.h \
  ../include/etc/vlistwidget.h \
  ../include/graph/vgraphlink.h \
  ../include/graph/vgraphstream.h \
  ../include/graph/vgraph.h \
  ../include/graph/vgraphnode.h \
  ../include/log/vlogstdout.h \
  ../include/log/vlogstderr.h \
  ../include/log/vlogudp.h \
  ../include/log/vlogfile.h \
  ../include/log/vlog.h \
  ../include/log/vloglist.h \
  ../include/log/vlogfactory.h \
  ../include/log/vloghttp.h \
  ../include/log/vlognull.h \
  ../include/log/vlogdbwin32.h \
  ../include/base/vmemoryleak.h \
  ../include/base/verror.h \
  ../include/base/vinstance.h \
  ../include/base/vdependency.h \
  ../include/base/vlinux.h \
  ../include/base/vmetaclass.h \
  ../include/base/vtick.h \
  ../include/base/vsystem.h \
  ../include/base/vobject.h \
  ../include/base/vwindows.h \
  ../include/base/vfactory.h \
  ../include/base/vfile.h \
  ../include/base/vdebugnew.h \
  ../include/base/vdebugnewcancel.h \
  ../include/base/vobjectwidget.h \
  ../include/base/vrwobject.h \
  ../include/base/vapp.h \
  ../include/base/vthread.h \
  ../include/base/vxmldoc.h \
  ../include/base/vperformance.h \
  ../include/base/vexception.h \
  ../include/base/vxml.h \
  ../include/base/vprimitive.h \
  ../include/net/vudpsession.h \
  ../include/net/vudpclient.h \
  ../include/net/vudpserver.h \
  ../include/net/vsslclient.h \
  ../include/net/vnetfactory.h \
  ../include/net/vnet.h \
  ../include/net/vtcpserver.h \
  ../include/net/vnetclient.h \
  ../include/net/vtcpclient.h \
  ../include/net/vnetserver.h \
  ../include/net/vsslserver.h \
  ../include/net/http/vwebproxy.h \
  ../include/net/http/vhttpresponse.h \
  ../include/net/http/vhttpchunkbody.h \
  ../include/net/http/vwebproxywidget.h \
  ../include/net/http/vhttpheader.h \
  ../include/net/http/vhttprequest.h \
  ../include/net/vnetsession.h \
  ../include/net/vtcpsession.h \
  ../include/net/vsslsession.h \
	../include/base/vbase.h \
    ../include/net/vsslbase.h \
    ../include/net/http/vhttpbase.h
