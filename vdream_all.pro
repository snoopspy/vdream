TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
	lib/vdream.pro \
	lib/vdream_gui.pro \
	lib/vdream_test.pro \
	app/test/common_test \
	app/tool/getline \
	app/tool/logserver \
	app/tool/netc \
	app/tool/netclient \
	app/tool/nets \
	app/tool/netserver \
	app/tool/vdreamtest \
	app/tool/vlog \
	app/tool/webproxy

