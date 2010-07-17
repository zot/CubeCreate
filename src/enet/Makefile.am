AUTOMAKE_OPTIONS     = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = \
    -I$(top_srcdir) \
    -Iinclude \
    \
    -DHAS_SOCKLEN_T=1 \
    -Wno-error

lib_LTLIBRARIES = libenet_@bin_suffix@.la
libenet_@bin_suffix@_la_SOURCES = callbacks.c compress.c host.c list.c packet.c peer.c protocol.c unix.c win32.c
libenet_@bin_suffix@_la_DEPENDENCIES = $(top_srcdir)/config.h
libenet_@bin_suffix@_la_LDFLAGS = $(AM_LDFLAGS) -version-info 1:0:0 -static
