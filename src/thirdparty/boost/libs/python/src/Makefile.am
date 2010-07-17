AUTOMAKE_OPTIONS     = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = \
    -I$(top_srcdir) \
    @PYTHON_CFLAGS@

if WINDOWS
    AM_CPPFLAGS += -DBOOST_PYTHON_DYNAMIC_LIB
    AM_CPPFLAGS += -DBOOST_AUTO_LINK_NOMANGLE
    AM_CPPFLAGS += -DBOOST_PYTHON_SOURCE
    AM_CPPFLAGS += -DBOOST_PYTHON_NO_LIB
    AM_CPPFLAGS += -DBOOST_ALL_NO_LIB
    AM_CPPFLAGS += -DWIN32 -DWINDOWS
    AM_CXXFLAGS = -O2 -Wall
    AM_CFLAGS = $(AM_CXXFLAGS)
else
    AM_CPPFLAGS += -DLINUX
    AM_CXXFLAGS = -O2 -Wall
    AM_CFLAGS = $(AM_CXXFLAGS)
endif


lib_LTLIBRARIES = libboost_python_@bin_suffix@.la

libboost_python_@bin_suffix@_la_SOURCES  = \
converter/builtin_converters.cpp \
converter/type_id.cpp \
converter/from_python.cpp \
converter/registry.cpp \
converter/arg_to_python_base.cpp \
tuple.cpp \
module.cpp \
str.cpp \
object_operators.cpp \
slice.cpp \
wrapper.cpp \
exec.cpp \
list.cpp \
object_protocol.cpp \
numeric.cpp \
long.cpp \
dict.cpp \
import.cpp \
object/inheritance.cpp \
object/pickle_support.cpp \
object/function_doc_signature.cpp \
object/iterator.cpp \
object/function.cpp \
object/class.cpp \
object/life_support.cpp \
object/stl_iterator.cpp \
object/enum.cpp \
errors.cpp

libboost_python_@bin_suffix@_la_DEPENDENCIES = $(top_srcdir)/config.h
libboost_python_@bin_suffix@_la_LDFLAGS = -static
