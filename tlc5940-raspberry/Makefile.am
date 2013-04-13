## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	-D_GLIBCXX_USE_NANOSLEEP

AM_CFLAGS =\
	 -Wall\
	 -g\
	 -std=c++11 

AM_CXXFLAGS =\
	-std=c++11 

lib_LTLIBRARIES = libtlc5940-raspberry-@PACKAGE_VERSION@.la

libtlc5940_raspberry_@PACKAGE_VERSION@_la_SOURCES = \
	gpio.h \
	gpio.cpp \
	raspberry-gpio.h \
	raspberry-gpio.cpp \
	tlc-controller.h

libtlc5940_raspberry_@PACKAGE_VERSION@_la_LDFLAGS = \
	-version-info $(LT_VERSION)

libtlc5940_raspberry_@PACKAGE_VERSION@_la_LIBADD = \
	-lpthread \
	-lwiringPi

libtlc5940_raspberry_@PACKAGE_VERSION@_la_includedir = $(includedir)/tlc5940-raspberry-$(PACKAGE_VERSION)/tlc5940-raspberry
libtlc5940_raspberry_@PACKAGE_VERSION@_la_include_HEADERS = \
	gpio.h \
	raspberry-gpio.h \
	tlc-controller.h


