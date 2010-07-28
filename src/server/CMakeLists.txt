#
# CMake for CubeCreate
# -------------------------
# this makes server binary.
#

# include sdl and python headers
include_directories(${SDL_INCLUDE_DIR} ${SDLMIXER_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR} ${PYTHON_INCLUDE_PATH})

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux") # there is no LINUX variable declared
   add_definitions (-fsigned-char)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# now, include v8
include_directories(${CMAKE_SOURCE_DIR}/src/thirdparty/v8/include)
# server def and executable build
add_definitions(-DSERVER)
set(SERVER_SOURCES
    ../intensity/editing_system
    ../shared/tools
    ../engine/server
    ../engine/serverbrowser
    ../fpsgame/fps
    ../fpsgame/server
    ../fpsgame/client
    ../fpsgame/entities
    ../intensity/python_wrap
    ../intensity/system_manager
    ../intensity/message_system
    ../intensity/server_system
    ../intensity/logging
    ../intensity/messages
    ../intensity/utility
    ../engine/world
    ../engine/worldio
    ../intensity/engine_additions
    ../engine/command
    ../engine/octa
    ../engine/physics
    ../engine/rendermodel
    ../engine/normal
    ../engine/bih
    ../shared/geom
    ../engine/client
    ../intensity/world_system
    ../engine/octaedit
    ../intensity/steering
    ../intensity/targeting
    ../intensity/network_system
    ../intensity/script_engine_manager
    ../intensity/script_engine
    ../intensity/script_engine_v8
    ../intensity/fpsserver_interface
    ../intensity/fpsclient_interface
    ../intensity/intensity_physics
    ../intensity/intensity_physics_sauer
    ../engine/octarender
    ../fpsgame/weapon
    ../intensity/master
    ../shared/stream
    ../engine/pvs
    ../engine/blend
    ../shared/zip
    ../intensity/shared_module_members_boost
    ../intensity/NPC
    ${EXTRA_SOURCES}
)

# link libs to executable
set(SERVER_LIBRARIES
    enet_${CC_BUILD_SUFFIX}
    V8_${CC_BUILD_SUFFIX}
    ${PYTHON_LIBRARIES}
    boost_python_${CC_BUILD_SUFFIX}
    ${SDL_LIBRARY}
    ${SDLMIXER_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLSOUND_LIBRARY}
    ${ZLIB_LIBRARIES}
    ${UTIL}
)

# additional libs on windows
if (MINGW OR WIN32)
    set(SERVER_LIBRARIES ${SERVER_LIBRARIES} ws2_32 opengl32 winmm)
    if (NOT MINGW)
        set(SERVER_LIBRARIES ${SERVER_LIBRARIES} msvcrt)
    endif (NOT MINGW)
endif (MINGW OR WIN32)

if (${CMAKE_SYSTEM_NAME} MATCHES "BSD") # there is no BSD variable declared
    set(SERVER_LIBRARIES ${SERVER_LIBRARIES} execinfo)
endif (${CMAKE_SYSTEM_NAME} MATCHES "BSD")

# finally build and link executable
add_executable(CC_Server_${CC_BUILD_SUFFIX} ${SERVER_SOURCES})
target_link_libraries(CC_Server_${CC_BUILD_SUFFIX} ${SERVER_LIBRARIES})
install(TARGETS CC_Server_${CC_BUILD_SUFFIX}
        RUNTIME DESTINATION bin
)
