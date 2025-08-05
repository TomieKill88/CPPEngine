#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------
set(TARGET_NAME sfml_libs)
		   
add_library(${TARGET_NAME} STATIC)

#--------------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------------
list(APPEND sfml_libs_SOURCES  # sources
								sfml/sfmlTest.hpp
								sfml/sfmlTest.cpp)

target_sources(${TARGET_NAME} PRIVATE ${sfml_libs_SOURCES})

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
# State that anybody linking to sfmlLib needs to include the current source directory
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})