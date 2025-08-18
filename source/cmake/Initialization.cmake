set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

#--------------------------------------------------------------------------
# Include CMake Modules
#--------------------------------------------------------------------------
include(GNUInstallDirs)

#--------------------------------------------------------------------------
# Include OWN CMake Modules
#--------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/paths)
include(paths)
