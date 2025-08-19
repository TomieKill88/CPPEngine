#--------------------------------------------------------------------------
# SOURCES
#--------------------------------------------------------------------------
set(LIBRARIES_DIRECTORY "${PROJECT_SOURCE_DIR}/src" CACHE PATH "Path to projects own libraries")

#--------------------------------------------------------------------------
# OUTPUT
#--------------------------------------------------------------------------
set(OUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/out" CACHE PATH "Output directory for debugging")

#--------------------------------------------------------------------------
# INSTALL
#--------------------------------------------------------------------------
set(INSTALL_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/target" CACHE PATH "Install directory for project")
set(INSTALL_BINDIR "${INSTALL_DIRECTORY}/bin" CACHE PATH "Install directory for project binaries")
set(INSTALL_LIBDIR "${INSTALL_DIRECTORY}/lib" CACHE PATH "Install directory for project libs")
set(INSTALL_INCLUDEDIR "${INSTALL_DIRECTORY}/include" CACHE PATH "Install directory for project public header")

#--------------------------------------------------------------------------
# EXTERNAL
#--------------------------------------------------------------------------
set(EXT_LIBRARIES_DIRECTORY "C:/Repositories" CACHE PATH "Path to external libraries")

set(sfml_DIRECTORY "${EXT_LIBRARIES_DIRECTORY}/SFML-2.6.2" CACHE PATH "Path to SFML")
set(sfml_BINDIR "${sfml_DIRECTORY}/bin" CACHE PATH "Path to sfml binaries")
set(sfml_LIBDIR "${sfml_DIRECTORY}/lib" CACHE PATH "Path to sfml libs")
set(sfml_INCLUDEDIR "${sfml_DIRECTORY}/include" CACHE PATH "Path to sfml includes")