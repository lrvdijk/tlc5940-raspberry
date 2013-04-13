## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = tlc5940-raspberry example

tlc5940docdir = ${prefix}/doc/tlc5940-raspberry
tlc5940doc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog

EXTRA_DIST = $(tlc5940doc_DATA)

# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(tlc5940docdir)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = tlc5940-raspberry-1.0.pc
