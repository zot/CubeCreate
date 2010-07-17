# get rid of that stupid cache mechanism
rm -f config.cache

AC_INIT(cubecreate, 0.1.0, quaker66@gmail.com)
AC_PREREQ(2.52)
AC_CONFIG_SRCDIR(configure.ac)

AM_INIT_AUTOMAKE(1.6 dist-bzip2)
AM_CONFIG_HEADER(config.h)
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_PROG_CXX
AC_PROG_CC
AC_PROG_OBJC

define([AC_LIBTOOL_LANG_CXX_CONFIG], [:])dnl
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])dnl
LT_INIT

AC_PREFIX_DEFAULT([$(pwd .)])

# based on host OS, export some conditionals
case "$host_os" in
   mingw*)
      windows=true
      ;;
   darwin*)
      mac=true
      ;;
   *bsd*)
      bsd=true
      ;;
   *)
      linux=true
      ;;
esac

AM_CONDITIONAL([WINDOWS], [test x$windows = xtrue])
AM_CONDITIONAL([MACOSX], [test x$mac = xtrue])
AM_CONDITIONAL([BSD], [test x$bsd = xtrue])
AM_CONDITIONAL([LINUX], [test x$linux = xtrue])

bin_suffix="${build_os}-${build_cpu}"
AC_SUBST(bin_suffix)

PKG_CHECK_MODULES([GL], [gl])
PKG_CHECK_MODULES([ZLIB], [zlib])

SDL_CONFIG="sdl-config"
AC_ARG_WITH(sdl-config,
[  --with-sdl-config=FILE   sdl-config to use (/usr/bin/sdl-config)],
[
   SDL_CONFIG=$withval
   AC_CHECK_PROG(SDL_CONFIG_IN_PATH, $SDL_CONFIG, yes, no)
   if test $SDL_CONFIG_IN_PATH = no; then
      AC_MSG_ERROR([Fatal Error: no sdl-config detected.])
   fi
   ],
[
  AC_CHECK_PROG(SDL_CONFIG_IN_PATH, $SDL_CONFIG, yes, no)
  if test $SDL_CONFIG_IN_PATH = no; then
    AC_MSG_ERROR([Fatal Error: no sdl-config detected.])
  fi
])

SDL_CFLAGS=`$SDL_CONFIG --cflags`
SDL_LIBS=`$SDL_CONFIG --libs`

AC_CHECK_LIB([SDL_mixer], [Mix_OpenAudio], [SDL_LIBS="$SDL_LIBS -lSDL_mixer"], [AC_MSG_ERROR([Fatal Error: no SDL_mixer detected.])], [`sdl-config --libs --cflags`])
AC_CHECK_LIB([SDL_sound], [Sound_Init], [SDL_LIBS="$SDL_LIBS -lSDL_sound"], [AC_MSG_ERROR([Fatal Error: no SDL_sound detected.])], [`sdl-config --libs --cflags`])
AC_CHECK_LIB([SDL_image], [IMG_Init], [SDL_LIBS="$SDL_LIBS -lSDL_image"], [AC_MSG_ERROR([Fatal Error: no SDL_image detected.])], [`sdl-config --libs --cflags`])
AC_CHECK_LIB([SDL_ttf], [TTF_Init], [SDL_LIBS="$SDL_LIBS -lSDL_ttf"], [AC_MSG_ERROR([Fatal Error: no SDL_ttf detected.])], [`sdl-config --libs --cflags`])

AC_SUBST(SDL_CFLAGS)
AC_SUBST(SDL_LIBS)

PYTHON_CONFIG="python-config"
AC_ARG_WITH(python-config,
[  --with-python-config=FILE   python-config to use (/usr/bin/python-config)],
[
   PYTHON_CONFIG=$withval
   AC_CHECK_PROG(PYTHON_CONFIG_IN_PATH, $PYTHON_CONFIG, yes, no)
   if test $PYTHON_CONFIG_IN_PATH = no; then
      AC_MSG_ERROR([Fatal Error: no python-config detected.])
   fi
   ],
[
  AC_CHECK_PROG(PYTHON_CONFIG_IN_PATH, $PYTHON_CONFIG, yes, no)
  if test $PYTHON_CONFIG_IN_PATH = no; then
    AC_MSG_ERROR([Fatal Error: no python-config detected.])
  fi
])

AC_SUBST(PYTHON_CFLAGS)
AC_SUBST(PYTHON_LIBS)
PYTHON_CFLAGS=`$PYTHON_CONFIG --cflags|sed 's/-Wstrict-prototypes//'` # workaround - get rid of C flag when using this for C++
PYTHON_LIBS=`$PYTHON_CONFIG --libs`

AC_ARG_ENABLE([web-plugin],
   [AC_HELP_STRING([--enable-web-plugin], [enable build of webbrowser plugin. @<:@default=no@:>@])],
   [
    if test "x${enableval}" = "xyes" ; then
       enable_web_plugin="yes"
    else
       enable_web_plugin="no"
    fi
   ],
   [enable_web_plugin="no"]
)

AC_MSG_CHECKING([whether web browser plugin is built])
AC_MSG_RESULT([${enable_web_plugin}])

have_web_plugin="no"

if test "x${enable_web_plugin}" = "xyes" ; then
    PKG_CHECK_MODULES([GTK], [gtk+-2.0])
    PKG_CHECK_MODULES([XT], [xt])
    have_web_plugin="yes"
fi
AM_CONDITIONAL([INTENSITY_PLUGIN], [test x$have_web_plugin = xyes])

AC_OUTPUT([
Makefile
src/Makefile
src/thirdparty/Makefile
src/thirdparty/boost/Makefile
src/thirdparty/boost/libs/Makefile
src/thirdparty/boost/libs/python/Makefile
src/thirdparty/boost/libs/python/src/Makefile
src/enet/Makefile
src/client/Makefile
src/client/plugin/Makefile
src/client/plugin_listener/Makefile
src/server/Makefile
])

echo
echo
echo
echo "------------------------------------------------------------------------"
echo "$PACKAGE $VERSION $bin_suffix"
echo "------------------------------------------------------------------------"
echo
echo "Build with support for web browser plugin .... $have_web_plugin"
echo
echo "------------------------------------------------------------------------"
echo
echo "Now type 'make' ('gmake' on some systems) to compile $PACKAGE,"
echo "and then afterwards as root (or the user who will install this), type"
echo "'make install'. Change users with 'su' or 'sudo' appropriately."
echo
