#--------------------------------------------------------------------------
# C++ Standard
#--------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)


#--------------------------------------------------------------------------
# Include CMake Modules
#--------------------------------------------------------------------------
include(GNUInstallDirs)

#--------------------------------------------------------------------------
# Include OWN CMake Modules
#--------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/paths)
include(paths)


#--------------------------------------------------------------------------
# Output Directories
#--------------------------------------------------------------------------
# Set Output Directories to make debugging easy. Externall DLLs have
# to be sent here too or the Debugger wont find them
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_DIRECTORY})
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUT_DIRECTORY})