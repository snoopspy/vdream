CONFIG += VDREAM_LIB_BUILD
include (vdream.pri)

TARGET   = $${VDREAM_LIB_NAME}
TEMPLATE = lib
CONFIG  += staticlib
DESTDIR  = $${PWD}/lib

SOURCES += \
	$${PWD}/src/base/vapp.cpp \
	$${PWD}/src/base/vbase.cpp \
	$${PWD}/src/base/vdebugnew.cpp \
	$${PWD}/src/base/vdependency.cpp \
	$${PWD}/src/base/verror.cpp \
	$${PWD}/src/base/vfactory.cpp \
	$${PWD}/src/base/vfile.cpp \
	$${PWD}/src/base/vinstance.cpp \
	$${PWD}/src/base/vmemoryleak.cpp \
	$${PWD}/src/base/vobject.cpp \
	$${PWD}/src/base/vobjectwidget.cpp \
	$${PWD}/src/base/vperformance.cpp \
	$${PWD}/src/base/vprimitive.cpp \
	$${PWD}/src/base/vrwobject.cpp \
	$${PWD}/src/base/vstate.cpp \
	$${PWD}/src/base/vstateobject.cpp \
	$${PWD}/src/base/vsystem.cpp \
	$${PWD}/src/base/vthread.cpp \
	$${PWD}/src/base/vtick.cpp \
	$${PWD}/src/base/vxml.cpp \
	$${PWD}/src/base/vxmldoc.cpp \
	$${PWD}/src/etc/vdatachange.cpp \
	$${PWD}/src/etc/vdatafind.cpp \
	$${PWD}/src/etc/vint.cpp \
	$${PWD}/src/etc/vlistwidget.cpp \
	$${PWD}/src/etc/vmyobject.cpp \
	$${PWD}/src/graph/vgraph.cpp \
	$${PWD}/src/graph/vgraphlink.cpp \
	$${PWD}/src/graph/vgraphnode.cpp \
	$${PWD}/src/graph/vgraphstream.cpp \
	$${PWD}/src/log/vlog.cpp \
	$${PWD}/src/log/vlogdbwin32.cpp \
	$${PWD}/src/log/vlogfactory.cpp \
	$${PWD}/src/log/vlogfile.cpp \
	$${PWD}/src/log/vloghttp.cpp \
	$${PWD}/src/log/vloglist.cpp \
	$${PWD}/src/log/vlognull.cpp \
	$${PWD}/src/log/vlogstderr.cpp \
	$${PWD}/src/log/vlogstdout.cpp \
	$${PWD}/src/log/vlogudp.cpp \
	$${PWD}/src/net/http/vhttpchunkbody.cpp \
	$${PWD}/src/net/http/vhttpheader.cpp \
	$${PWD}/src/net/http/vhttprequest.cpp \
	$${PWD}/src/net/http/vhttpresponse.cpp \
	$${PWD}/src/net/http/vwebproxy.cpp \
	$${PWD}/src/net/http/vwebproxywidget.cpp \
	$${PWD}/src/net/vnet.cpp \
	$${PWD}/src/net/vnetclient.cpp \
	$${PWD}/src/net/vnetfactory.cpp \
	$${PWD}/src/net/vnetserver.cpp \
	$${PWD}/src/net/vsslbase.cpp \
	$${PWD}/src/net/vsslclient.cpp \
	$${PWD}/src/net/vsslserver.cpp \
	$${PWD}/src/net/vsslsession.cpp \
	$${PWD}/src/net/vtcpclient.cpp \
	$${PWD}/src/net/vtcpserver.cpp \
	$${PWD}/src/net/vtcpsession.cpp \
	$${PWD}/src/net/vudpclient.cpp \
	$${PWD}/src/net/vudpserver.cpp \
	$${PWD}/src/net/vudpsession.cpp

HEADERS += \
	$${PWD}/src/base/vapp.h \
	$${PWD}/src/base/vbase.h \
	$${PWD}/src/base/vdebugnew.h \
	$${PWD}/src/base/vdebugnewcancel.h \
	$${PWD}/src/base/vdependency.h \
	$${PWD}/src/base/verror.h \
	$${PWD}/src/base/vfactory.h \
	$${PWD}/src/base/vfile.h \
	$${PWD}/src/base/vinstance.h \
	$${PWD}/src/base/vlinux.h \
	$${PWD}/src/base/vmemoryleak.h \
	$${PWD}/src/base/vobject.h \
	$${PWD}/src/base/vobjectwidget.h \
	$${PWD}/src/base/vperformance.h \
	$${PWD}/src/base/vprimitive.h \
	$${PWD}/src/base/vrwobject.h \
	$${PWD}/src/base/vstate.h \
	$${PWD}/src/base/vstateobject.h \
	$${PWD}/src/base/vsystem.h \
	$${PWD}/src/base/vthread.h \
	$${PWD}/src/base/vtick.h \
	$${PWD}/src/base/vwindows.h \
	$${PWD}/src/base/vxml.h \
	$${PWD}/src/base/vxmldoc.h \
	$${PWD}/src/etc/vdatachange.h \
	$${PWD}/src/etc/vdatafind.h \
	$${PWD}/src/etc/vint.h \
	$${PWD}/src/etc/vlistwidget.h \
	$${PWD}/src/etc/vmyobject.h \
	$${PWD}/src/graph/vgraph.h \
	$${PWD}/src/graph/vgraphlink.h \
	$${PWD}/src/graph/vgraphnode.h \
	$${PWD}/src/graph/vgraphstream.h \
	$${PWD}/src/log/vlog.h \
	$${PWD}/src/log/vlogdbwin32.h \
	$${PWD}/src/log/vlogfactory.h \
	$${PWD}/src/log/vlogfile.h \
	$${PWD}/src/log/vloghttp.h \
	$${PWD}/src/log/vloglist.h \
	$${PWD}/src/log/vlognull.h \
	$${PWD}/src/log/vlogstderr.h \
	$${PWD}/src/log/vlogstdout.h \
	$${PWD}/src/log/vlogudp.h \
	$${PWD}/src/net/http/vhttpbase.h \
	$${PWD}/src/net/http/vhttpchunkbody.h \
	$${PWD}/src/net/http/vhttpheader.h \
	$${PWD}/src/net/http/vhttprequest.h \
	$${PWD}/src/net/http/vhttpresponse.h \
	$${PWD}/src/net/http/vwebproxy.h \
	$${PWD}/src/net/http/vwebproxywidget.h \
	$${PWD}/src/net/vnet.h \
	$${PWD}/src/net/vnetclient.h \
	$${PWD}/src/net/vnetfactory.h \
	$${PWD}/src/net/vnetserver.h \
	$${PWD}/src/net/vnetsession.h \
	$${PWD}/src/net/vsslbase.h \
	$${PWD}/src/net/vsslclient.h \
	$${PWD}/src/net/vsslserver.h \
	$${PWD}/src/net/vsslsession.h \
	$${PWD}/src/net/vtcpclient.h \
	$${PWD}/src/net/vtcpserver.h \
	$${PWD}/src/net/vtcpsession.h \
	$${PWD}/src/net/vudpclient.h \
	$${PWD}/src/net/vudpserver.h \
	$${PWD}/src/net/vudpsession.h

contains(QT, gui) {
FORMS += \
	$${PWD}/src/etc/vlistwidget.ui \
	$${PWD}/src/net/http/vwebproxywidget.ui
}
