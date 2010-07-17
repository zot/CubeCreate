AUTOMAKE_OPTIONS     = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = \
    -I$(top_srcdir) \
    -I$(top_srcdir)/src/shared \
    -I$(top_srcdir)/src/engine \
    -I$(top_srcdir)/src/fpsgame \
    -I$(top_srcdir)/src/intensity \
    -I$(top_srcdir)/src/enet/include \
    -I$(top_srcdir)/src/thirdparty/v8/include \
    \
    -DSERVER \
    -fsigned-char \
    @ZLIB_CFLAGS@ \
    @PYTHON_CFLAGS@ \
    @SDL_CFLAGS@

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

bin_PROGRAMS = ../cc_server_@bin_suffix@

___cc_server_@bin_suffix@_SOURCES = ../intensity/editing_system.cpp \
    ../shared/tools.cpp \
    ../engine/server.cpp \
    ../engine/serverbrowser.cpp \
    ../fpsgame/fps.cpp \
    ../fpsgame/gserver.cpp \
    ../fpsgame/gclient.cpp \
    ../fpsgame/entities.cpp \
    ../intensity/python_wrap.cpp \
    ../intensity/system_manager.cpp \
    ../intensity/message_system.cpp \
    ../intensity/server_system.cpp \
    ../intensity/logging.cpp \
    ../intensity/messages.cpp \
    ../intensity/utility.cpp \
    ../engine/world.cpp \
    ../engine/worldio.cpp \
    ../intensity/engine_additions.cpp \
    ../engine/command.cpp \
    ../engine/octa.cpp \
    ../engine/physics.cpp \
    ../engine/rendermodel.cpp \
    ../engine/normal.cpp \
    ../engine/bih.cpp \
    ../shared/geom.cpp \
    ../engine/client.cpp \
    ../intensity/world_system.cpp \
    ../engine/octaedit.cpp \
    ../intensity/steering.cpp \
    ../intensity/targeting.cpp \
    ../intensity/network_system.cpp \
    ../intensity/script_engine_manager.cpp \
    ../intensity/script_engine.cpp \
    ../intensity/script_engine_v8.cpp \
    ../intensity/fpsserver_interface.cpp \
    ../intensity/fpsclient_interface.cpp \
    ../intensity/intensity_physics.cpp \
    ../intensity/intensity_physics_sauer.cpp \
    ../engine/octarender.cpp \
    ../fpsgame/weapon.cpp \
    ../intensity/master.cpp \
    ../shared/stream.cpp \
    ../engine/pvs.cpp \
    ../engine/blend.cpp \
    ../shared/zip.cpp \
    ../intensity/shared_module_members_boost.cpp \
    ../intensity/NPC.cpp

if MACOSX
    ___cc_server_@bin_suffix@_SOURCES += ../osx_dev/macutils.mm ../osx_dev/SDLMain.m
endif

___cc_server_@bin_suffix@_LDADD = \
    @ZLIB_LIBS@ \
    @PYTHON_LIBS@ \
    @SDL_LIBS@ \
    $(top_srcdir)/src/enet/libenet_@bin_suffix@.la \
    $(top_srcdir)/src/thirdparty/boost/libs/python/src/libboost_python_@bin_suffix@.la

if WINDOWS
    ___cc_server_@bin_suffix@_LDADD += $(top_srcdir)/src/thirdparty/v8/libv8.lib -lws2_32 -lwinmm -lmsvcrt -lopengl32
else
    ___cc_server_@bin_suffix@_LDADD += $(top_srcdir)/src/thirdparty/v8/libv8.a
if LINUX
    ___cc_server_@bin_suffix@_LDADD += -lutil
endif
if BSD
    ___cc_server_@bin_suffix@_LDADD += -lutil -lexecinfo
endif
endif
