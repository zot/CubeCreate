AUTOMAKE_OPTIONS     = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in

if INTENSITY_PLUGIN
    SUBDIRS = plugin_listener plugin
endif

AM_CPPFLAGS = \
    -I$(top_srcdir) \
    -I$(top_srcdir)/src/shared \
    -I$(top_srcdir)/src/engine \
    -I$(top_srcdir)/src/fpsgame \
    -I$(top_srcdir)/src/intensity \
    -I$(top_srcdir)/src/enet/include \
    -I$(top_srcdir)/src/thirdparty/v8/include \
    \
    -DCLIENT \
    @GL_CFLAGS@ \
    @ZLIB_CFLAGS@ \
    @PYTHON_CFLAGS@ \
    @SDL_CFLAGS@

if INTENSITY_PLUGIN
    AM_CPPFLAGS += -I$(top_srcdir)/src/client/plugin_listener \
                    -DINTENSITY_PLUGIN
endif

if WINDOWS
    AM_CPPFLAGS += -I$(top_srcdir)/src/windows/include -DWIN32 -DWINDOWS
    AM_CXXFLAGS = -g -O2 -Wall
    AM_CFLAGS = $(AM_CXXFLAGS)
else
    AM_CPPFLAGS += -DLINUX
    AM_CXXFLAGS = -g -O1 -Wall
    AM_CFLAGS = $(AM_CXXFLAGS)
endif

if LINUX
    AM_CPPFLAGS += -fsigned-char
endif

bin_PROGRAMS = ../cc_client_@bin_suffix@

___cc_client_@bin_suffix@_SOURCES = ../engine/3dgui.cpp \
    ../engine/blob.cpp \
    ../engine/blend.cpp \
    ../engine/menus.cpp \
    ../engine/serverbrowser.cpp \
    ../intensity/editing_system.cpp \
    ../intensity/messages.cpp \
    ../intensity/logging.cpp \
    ../intensity/message_system.cpp \
    ../intensity/system_manager.cpp \
    ../intensity/python_wrap.cpp \
    ../intensity/utility.cpp \
    ../intensity/client_system.cpp \
    ../intensity/client_engine_additions.cpp \
    ../intensity/character_render.cpp \
    ../intensity/intensity_physics.cpp \
    ../intensity/intensity_physics_sauer.cpp \
    ../fpsgame/fps.cpp \
    ../fpsgame/gserver.cpp \
    ../fpsgame/gclient.cpp \
    ../fpsgame/entities.cpp \
    ../fpsgame/render.cpp \
    ../fpsgame/weapon.cpp \
    ../shared/tools.cpp \
    ../shared/geom.cpp \
    ../engine/rendertext.cpp \
    ../engine/material.cpp \
    ../engine/octaedit.cpp \
    ../engine/grass.cpp \
    ../engine/physics.cpp \
    ../engine/rendergl.cpp \
    ../engine/worldio.cpp \
    ../engine/texture.cpp \
    ../engine/console.cpp \
    ../engine/world.cpp \
    ../engine/glare.cpp \
    ../engine/renderva.cpp \
    ../engine/normal.cpp \
    ../engine/rendermodel.cpp \
    ../engine/shadowmap.cpp \
    ../engine/main.cpp \
    ../engine/bih.cpp \
    ../engine/octa.cpp \
    ../engine/lightmap.cpp \
    ../engine/water.cpp \
    ../engine/shader.cpp \
    ../engine/rendersky.cpp \
    ../engine/renderparticles.cpp \
    ../engine/octarender.cpp \
    ../engine/server.cpp \
    ../engine/client.cpp \
    ../engine/dynlight.cpp \
    ../engine/decal.cpp \
    ../engine/sound.cpp \
    ../engine/pvs.cpp \
    ../engine/command.cpp \
    ../intensity/engine_additions.cpp \
    ../intensity/world_system.cpp \
    ../intensity/targeting.cpp \
    ../intensity/steering.cpp \
    ../intensity/network_system.cpp \
    ../intensity/script_engine_manager.cpp \
    ../intensity/script_engine.cpp \
    ../intensity/script_engine_v8.cpp \
    ../intensity/fpsclient_interface.cpp \
    ../intensity/fpsserver_interface.cpp \
    ../intensity/master.cpp \
    ../intensity/intensity_gui.cpp \
    ../shared/stream.cpp \
    ../shared/zip.cpp \
    ../engine/movie.cpp \
    ../intensity/shared_module_members_boost.cpp \
    ../fpsgame/scoreboard.cpp

if MACOSX
    ___cc_client_@bin_suffix@_SOURCES += ../osx_dev/macutils.mm ../osx_dev/SDLMain.m
endif

___cc_client_@bin_suffix@_LDADD = \
    @GL_LIBS@ \
    @ZLIB_LIBS@ \
    @PYTHON_LIBS@ \
    @SDL_LIBS@ \
    $(top_srcdir)/src/enet/libenet_@bin_suffix@.la \
    $(top_srcdir)/src/thirdparty/boost/libs/python/src/libboost_python_@bin_suffix@.la \
    -lrt

if INTENSITY_PLUGIN
    ___cc_client_@bin_suffix@_LDADD += $(top_srcdir)/src/client/plugin_listener/libplugin_listener_@bin_suffix@.la
endif

if WINDOWS
    ___cc_client_@bin_suffix@_LDADD += $(top_srcdir)/src/thirdparty/v8/libv8.lib \
                                    $(top_srcdir)/src/windows/lib/zdll.lib \
                                    -lopengl32 -lglu32 -lws2_32 -lwinmm -lmsvcrt -luser32 -limagehlp
else
if LINUX
    ___cc_client_@bin_suffix@_LDADD += $(top_srcdir)/src/thirdparty/v8/libv8.a -lutil
endif
if BSD
    ___cc_client_@bin_suffix@_LDADD += $(top_srcdir)/src/thirdparty/v8/libv8.a -lutil -lexecinfo
endif
endif
