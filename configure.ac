dnl Process this file with autoconf to produce a configure script.
AC_INIT(tlc5940-raspberry, [1.0])

AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.11])
AM_SILENT_RULES([yes])
AC_PROG_CXX([g++-4.7 g++])

LT_INIT

AC_SUBST([LT_VERSION], [1:0:0])

AC_CONFIG_FILES([
	Makefile
	tlc5940-raspberry-${PACKAGE_VERSION}.pc
	tlc5940-raspberry/Makefile
	example/Makefile
])

AC_OUTPUT
