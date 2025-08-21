cmake_minimum_required(VERSION 3.26)

# https://cmake.org/cmake/help/v3.26/command/project.html#command:project
project( cpp-engine
		VERSION 0.0.1
		DESCRIPTION "Small Cpp Game Engine with SFLM and ImGUI"
		LANGUAGES CXX)

# Add /cmake to CMAKE_MODULE_PATH and call Initialization.cmake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(Initialization)

option(BUILD_SHARED_LIBS OFF)
option(BUILD_UNIT_TESTS OFF)

# Dependencies
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/dependencies/sfml)
include(sfml)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/dependencies/imgui)
include(imgui)

# Libraries and applications
add_subdirectory(app)
add_subdirectory(src)

if(BUILD_UNIT_TESTS)
	add_subdirectory(tests)
endif()

