all: 
	make build

update:
	git pull

build:
	make debug
	make release
	make app_

debug: libvdream_d libvdream_test_d libvdream_gui_d libvdream_gui_test_d  

release: libvdream libvdream_test libvdream_gui libvdream_gui_test

libvdream_d:
	qmake libvdream.pro CONFIG+=debug
	make -j8 -f Makefile
	make clean -f Makefile

libvdream_test_d:
	qmake libvdream_test.pro CONFIG+=debug
	make -j8 -f Makefile
	make clean -f Makefile

libvdream_gui_d:
	qmake libvdream_gui.pro CONFIG+=debug
	make -j8 -f Makefile
	cp ui_* src
	make clean -f Makefile

libvdream_gui_test_d:
	qmake libvdream_gui_test.pro CONFIG+=debug
	make -j8 -f Makefile
	cp ui_* src
	make clean -f Makefile

libvdream:
	qmake libvdream.pro CONFIG+=release
	make -j8 -f Makefile
	make clean -f Makefile

libvdream_test:
	qmake libvdream_test.pro CONFIG+=release
	make -j8 -f Makefile
	make clean -f Makefile

libvdream_gui:
	qmake libvdream_gui.pro CONFIG+=release
	make -j8 -f Makefile
	cp ui_* src
	make clean -f Makefile

libvdream_gui_test:
	qmake libvdream_gui_test.pro CONFIG+=release
	make -j8 -f Makefile
	cp ui_* src
	make clean -f Makefile

app_:
	cd app && \
	qmake vdream_app.pro CONFIG+=release && \
	make -j8 -f Makefile && \
	make clean -f Makefile && \
	cd ..

clean:
	echo "clean in GNUmakefile"
	rm -rf *.o
	rm -rf moc_*.*
	find -name Makefile -type f -delete

