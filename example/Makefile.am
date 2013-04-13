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

bin_PROGRAMS = tlc_example

tlc_example_SOURCES =  \
	main.cpp

tlc_example_CFLAGS = \
	-I$(top_builddir)

tlc_example_LDADD = $(top_builddir)/tlc5940-raspberry/libtlc5940-raspberry-@PACKAGE_VERSION@.la

tlc_example_LDFLAGS = \
	-lpthread

