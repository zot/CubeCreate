#
# CMake for CubeCreate
# -------------------------
# this makes server binary.
#

# include vcpp, sdl and python headers
if (WIN32 AND NOT MINGW)
    include_directories(${PLATFORM_SDK_A}/Include)
    include_directories(${PLATFORM_SDK_B}/Include)
endif (WIN32 AND NOT MINGW)
include_directories(${SDL_INCLUDE_DIR} ${SDLMIXER_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR} ${PYTHON_INCLUDE_PATH} ${LUA_INCLUDE_DIR})
if (NOT (WIN32 OR MINGW))
	include_directories(${Boost_INCLUDE_DIRS})
endif (NOT (WIN32 OR MINGW))

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux") # there is no LINUX variable declared
   add_definitions (-fsigned-char)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if (CMAKE_COMPILER_IS_GNUCXX)
	exec_program(${CMAKE_CXX_COMPILER}
		ARGS ${CMAKE_CXX_COMPILER_ARG1} -dumpversion
		OUTPUT_VARIABLE _cc_gnucxx_ver
	)

	string(REGEX REPLACE "([0-9])\\.([0-9])(\\.[0-9])?" "\\1\\2" # taken from findboost.cmake
		_cc_gnucxx_ver ${_cc_gnucxx_ver}
	)

	if ((_cc_gnucxx_ver EQUAL 44) OR (_cc_gnucxx_ver LESS 44))
		foreach (_cc_gnucxx_ver 4.6 4.5)
			find_program(_cc_gnucxx_cl g++-${_cc_gnucxx_ver})
			if (_cc_gnucxx_cl)
				message(STATUS "Found right G++ for building CC server: ${_cc_gnucxx_cl}. Overriding defaults because of C++0x features support.")
				set(CMAKE_CXX_COMPILER ${_cc_gnucxx_cl})
				add_definitions(-std=c++0x)
				break()
			endif (_cc_gnucxx_cl)
		endforeach (_cc_gnucxx_ver 4.6 4.5)

		if (NOT _cc_gnucxx_cl)
			message(FATAL_ERROR "Could not find g++ version with required C++0x features support (4.5+). You can also try using Clang.")
		endif (NOT _cc_gnucxx_cl)
	endif ((_cc_gnucxx_ver EQUAL 44) OR (_cc_gnucxx_ver LESS 44))
endif (CMAKE_COMPILER_IS_GNUCXX)

# include JSON.
include_directories(${CMAKE_SOURCE_DIR}/src/thirdparty/json)
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
    ../intensity/script_engine_lua
    ../intensity/engine_variables
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
    ${LUA_LIBRARIES}
    ${PYTHON_LIBRARIES}
    ${SDL_LIBRARY}
    ${SDLMIXER_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLSOUND_LIBRARY}
    ${ZLIB_LIBRARIES}
    ${UTIL}
    json_${CC_BUILD_SUFFIX}
)

if (WIN32 OR MINGW)
	set(SERVER_LIBRARIES ${SERVER_LIBRARIES} boost_python_${CC_BUILD_SUFFIX})
else (WIN32 OR MINGW)
	set(SERVER_LIBRARIES ${SERVER_LIBRARIES} ${Boost_PYTHON_LIBRARY})
endif (WIN32 OR MINGW)

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
