#
# CMake for CubeCreate
# ----------------------------------
# just includes, links and proceeds.
#

# internal things
include_directories(shared engine fpsgame intensity enet/include thirdparty/boost include ${SDL_INCLUDE_DIR} ${SDLMIXER_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR} ${PYTHON_INCLUDE_PATH})
link_directories(${CMAKE_SOURCE_DIR}/src/enet)
link_directories(${CMAKE_SOURCE_DIR}/src/thirdparty/boost/libs/python)

# further proceed.
add_subdirectory(thirdparty)
add_subdirectory(enet)
add_subdirectory(server)
add_subdirectory(client)

