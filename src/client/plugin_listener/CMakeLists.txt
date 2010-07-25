#
# CMake for CubeCreate
# -----------------------------------------
# this builds a simple listener for plugin.
#

# has just one sources, build, link.
add_library(plugin_listener_${CC_BUILD_SUFFIX}
    intensity_plugin_listener.cpp
)
target_link_libraries(plugin_listener_${CC_BUILD_SUFFIX})
install(TARGETS plugin_listener_${CC_BUILD_SUFFIX}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
