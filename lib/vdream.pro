# CONFIG += VDREAM_LIB_BUILD # gilgil temp 2014.11.28
QT -= gui
#QT += gui widgets

include (../../../etc/gtest/gtest.pri) # gilgil temp 2014.11.28
include (vdream.pri)

TARGET   = $${VDREAM_LIB_NAME}
TEMPLATE = lib
CONFIG  += staticlib
DESTDIR  = ../lib

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
	../include/common/vrwobject.cpp \
	../include/common/vxmldoc.cpp \
	../include/common/vtick.cpp \
	../include/common/vperformance.cpp \
	../include/common/vexception.cpp \
	../include/common/vsecurelib.cpp \
	../include/common/vthread.cpp \
	../include/common/vsystem.cpp \
	../include/common/vdebugnew.cpp \
	../include/common/vobjectwidget.cpp \
	../include/common/vapp.cpp \
	../include/common/vmemoryleak.cpp \
	../include/common/veventhandler.cpp \
	../include/common/vstring.cpp \
	../include/common/vmetaclass.cpp \
	../include/common/vxml.cpp \
	../include/common/vfile.cpp \
	../include/common/vobject.cpp \
	../include/common/vinstance.cpp \
	../include/common/vbase.cpp \
	../include/common/vdependency.cpp \
	../include/common/vcommon.cpp \
	../include/common/verror.cpp \
	../include/net/vnetclient.cpp \
	../include/net/vsslcommon.cpp \
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
	../include/net/vnet.cpp

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
	../include/common/vmemoryleak.h \
	../include/common/verror.h \
	../include/common/vinstance.h \
	../include/common/vbase.h \
	../include/common/vdependency.h \
	../include/common/vlinux.h \
	../include/common/vmetaclass.h \
	../include/common/vstring.h \
	../include/common/veventhandler.h \
	../include/common/vtick.h \
	../include/common/vsystem.h \
	../include/common/vcommon.h \
	../include/common/vobject.h \
	../include/common/vsecurelib.h \
	../include/common/vwindows.h \
	../include/common/vfactory.h \
	../include/common/vfile.h \
	../include/common/vdebugnew.h \
	../include/common/vdebugnewcancel.h \
	../include/common/vobjectwidget.h \
	../include/common/vrwobject.h \
	../include/common/vapp.h \
	../include/common/vthread.h \
	../include/common/vxmldoc.h \
	../include/common/vperformance.h \
	../include/common/vexception.h \
	../include/common/vxml.h \
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
	../include/net/http/vhttpcommon.h \
	../include/net/http/vwebproxy.h \
	../include/net/http/vhttpresponse.h \
	../include/net/http/vhttpchunkbody.h \
	../include/net/http/vwebproxywidget.h \
	../include/net/http/vhttpheader.h \
	../include/net/http/vhttprequest.h \
	../include/net/vsslcommon.h \
	../include/net/vnetsession.h \
	../include/net/vtcpsession.h \
	../include/net/vsslsession.h
