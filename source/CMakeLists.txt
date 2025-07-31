cmake_minimum_required(VERSION 3.26)

# https://cmake.org/cmake/help/v3.26/command/project.html#command:project
project( cpp-engine
		VERSION 0.0.1
		DESCRIPTION "Small Cpp Game Engine with SFLM and ImGUI"
		LANGUAGES CXX)


# Add /cmake to CMAKE_MODULE_PATH and call Initialization.cmake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(Initialization)


add_subdirectory(app)
add_subdirectory(src)
#add_subdirectory(tests)