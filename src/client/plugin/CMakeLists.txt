#
# CMake for CubeCreate
# -------------------------------------
# this makes webbrowser plugin library.
# taken from original buildsystem
# slightly modified, commented
#

# plugin cpp flags
add_definitions(-DINTENSITY_PLUGIN)
add_definitions(-DINTENSITY_INSTALL_ROOT="${CMAKE_SOURCE_DIR}")

# set some sources. For that purpose, loop client ones
set(PLUGIN_SOURCES "")
foreach(source ${CLIENT_SOURCES})
    set(PLUGIN_SOURCES ${PLUGIN_SOURCES} ../${source})
endforeach(source)

# try to find pkg-config, fail if it can't
find_package(PkgConfig)
# find gtk in pkg-config.
pkg_check_modules(GTK gtk+-2.0)
include_directories(${GTK_INCLUDE_DIRS})
# find xt library.
pkg_check_modules(XT xt)
include_directories(${XT_INCLUDE_DIRS})

# when everything is successful, add cpp flags
add_definitions(-DXP_UNIX)
add_definitions(-DMOZ_X11)

# include some additional dirs
include_directories(. ./third_party/npapi/include ${CMAKE_SOURCE_DIR}/src/client/plugin_listener)

# more cpp flags!
add_definitions(-DO3D_PLUGIN_NAME="IntensityEngine")
add_definitions(-DO3D_PLUGIN_DESCRIPTION="The open source Intensity Engine plugin lets you play 3D games in your browser.")
add_definitions(-DO3D_PLUGIN_MIME_TYPE="application/x-intensityengine:int:IntensityEngine media")

# build a SHARED library of plugin.
add_library(intensity_plugin_${CC_BUILD_SUFFIX} SHARED
    base/logging.cc
    base/command_line.cc
    base/base_switches.cc
    base/debug_util.cc
    base/debug_util_posix.cc
    base/string_util.cc
    base/string_piece.cc
    base/string16.cc
    base/atomicops_internals_x86_gcc.cc
    base/lock_impl_posix.cc
    base/process_posix.cc
    base/process_util_linux.cc
    base/process_util_posix.cc
    base/file_descriptor_shuffle.cc
    base/file_util.cc
    base/file_util_linux.cc
    base/file_util_posix.cc
    base/file_path.cc
    base/thread_collision_warner.cc
    base/at_exit.cc
    base/time.cc
    base/time_posix.cc
    plugin/cross/o3d_glue.cc
    plugin/cross/main.cc
    plugin/linux/main_linux.cc
    third_party/nixysa/static_glue/npapi/npn_api.cc
    third_party/nixysa/static_glue/npapi/common.cc
    intensity_plugin.cpp
)

# link the plugin to client libs and xt libs.
target_link_libraries(intensity_plugin_${CC_BUILD_SUFFIX} ${CLIENT_LIBRARIES} ${XT_LIBRARIES})
install(TARGETS intensity_plugin_${CC_BUILD_SUFFIX}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
