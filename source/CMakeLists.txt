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

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/dependencies/imgui-sfml)
include(imgui-sfml)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/dependencies/nlohmann)
include(nlohmann)

# https://cmake.org/cmake/help/latest/module/FetchContent.html
# Projects should aim to declare the details of all dependencies they might use before they 
# call FetchContent_MakeAvailable() for any of them. This ensures that if any of the dependencies 
# are also sub-dependencies of one or more of the others, the main project still controls the 
# details that will be used
# NOTE: ImGui isnt here because after making ImGui available but BEFORE ImGui-SFML is fetched, we 
# need to set IMGUI_DIR to wherever CMake sent it using FetchContent_GetProperties
FetchContent_MakeAvailable(SFML ImGui-SFML json)

# Libraries and applications
add_subdirectory(app)
add_subdirectory(libs)

#if(BUILD_UNIT_TESTS)
#	list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/dependencies/unittests)
#	include(GoogleTests)

#	add_subdirectory(tests)
#endif()

# Install config files and resources
#--------------------------------------------------------------------------
# Resources (https://www.fontspace.com/category/ttf?p=2)
#--------------------------------------------------------------------------
list(APPEND resources  resources/AovelSans.ttf)
#--------------------------------------------------------------------------
# Config
#--------------------------------------------------------------------------						

list(APPEND config  app/config/appconfig.json)						

#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
install(FILES ${resources}
		DESTINATION ${INSTALL_BINDIR}/resources
)

install(FILES ${config}
		DESTINATION ${INSTALL_BINDIR}/config
)
