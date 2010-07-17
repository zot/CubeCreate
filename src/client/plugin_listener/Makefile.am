AUTOMAKE_OPTIONS     = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = \
    -I$(top_srcdir) \
    -I$(top_srcdir)/src/intensity \
    -DINTENSITY_PLUGIN \
    -DCLIENT

lib_LTLIBRARIES = libplugin_listener_@bin_suffix@.la
libplugin_listener_@bin_suffix@_la_SOURCES = intensity_plugin_listener.cpp
libplugin_listener_@bin_suffix@_la_DEPENDENCIES = $(top_srcdir)/config.h
libplugin_listener_@bin_suffix@_la_LDFLAGS = -static
