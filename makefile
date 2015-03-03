define makelib # $(1)filename, $(2)config
	cd lib && \
	qmake $(1) CONFIG+=$(2) && \
	make && \
	cp ui_* src \
	make clean && \
	cd ..
endef

all: 
	make debug
	make release
	make app_

update:
	git pull

debug: libvdream_d libvdream_test_d libvdream_gui_d libvdream_gui_test_d  

release: libvdream libvdream_test libvdream_gui libvdream_gui_test

libvdream_d:
	$(call makelib,libvdream.pro,debug)

libvdream_test_d:
	$(call makelib,libvdream_test.pro,debug)

libvdream_gui_d:
	$(call makelib,libvdream_gui.pro,debug)

libvdream_gui_test_d:
	$(call makelib,libvdream_gui_test.pro,debug)

libvdream:
	$(call makelib,libvdream.pro,release)

libvdream_test:
	$(call makelib,libvdream_test.pro,release)

libvdream_gui:
	$(call makelib,libvdream_gui.pro,release)

libvdream_gui_test:
	$(call makelib,libvdream_gui_test.pro,release)

app_:
	cd app && qmake && make && make clean && cd ..

clean:
	find -type d -name 'build-*'    -exec rm -r {} \;
	find -type f -name '*.o'        -delete
	find -type f -name '*.pro.user' -delete
	find -type f -name 'Makefile*'  -delete