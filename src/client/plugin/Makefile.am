AUTOMAKE_OPTIONS     = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = \
    -I$(top_srcdir) \
    -I$(top_srcdir)/src/client/plugin_listener \
    -I$(top_srcdir)/src/client/plugin/third_party/npapi/include \
    -I$(top_srcdir)/src/intensity \
    \
    -DINTENSITY_PLUGIN \
    -DCLIENT \
    -DINTENSITY_INSTALL_ROOT=\""$(top_srcdir)"\" \
    -DO3D_PLUGIN_NAME=\"IntensityEngine\" \
    -DO3D_PLUGIN_DESCRIPTION=\""The open source Intensity Engine plugin lets you play 3D games in your browser."\" \
    -DO3D_PLUGIN_MIME_TYPE=\""application/x-intensityengine:int:IntensityEngine media"\" \
    -DXP_UNIX \
    -DMOZ_X11 \
    @GTK_CFLAGS@ \
    @XT_CFLAGS@ \
    @SDL_CFLAGS@

lib_LTLIBRARIES = libintensity_plugin_@bin_suffix@.la

libintensity_plugin_@bin_suffix@_la_SOURCES = base/logging.cc \
    base/command_line.cc \
    base/base_switches.cc \
    base/debug_util.cc \
    base/debug_util_posix.cc \
    base/string_util.cc \
    base/string_piece.cc \
    base/string16.cc \
    base/atomicops_internals_x86_gcc.cc \
    base/lock_impl_posix.cc \
    base/process_posix.cc \
    base/process_util_linux.cc \
    base/process_util_posix.cc \
    base/file_descriptor_shuffle.cc \
    base/file_util.cc \
    base/file_util_linux.cc \
    base/file_util_posix.cc \
    base/file_path.cc \
    base/thread_collision_warner.cc \
    base/at_exit.cc \
    base/time.cc \
    base/time_posix.cc \
    plugin/cross/o3d_glue.cc \
    plugin/cross/main.cc \
    plugin/linux/main_linux.cc \
    third_party/nixysa/static_glue/npapi/npn_api.cc \
    third_party/nixysa/static_glue/npapi/common.cc \
    intensity_plugin.cpp

libintensity_plugin_@bin_suffix@_la_DEPENDENCIES = $(top_srcdir)/config.h
libintensity_plugin_@bin_suffix@_la_LIBADD = @GTK_LIBS@ \
    @XT_LIBS@ \
    @SDL_LIBS@ \
    $(top_srcdir)/src/client/plugin_listener/libplugin_listener_@bin_suffix@.la
