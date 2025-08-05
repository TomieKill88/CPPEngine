set(LIBRARIES_DIRECTORY "${PROJECT_SOURCE_DIR}/src" CACHE PATH "Path to projects own libraries")
set(EXT_LIBRARIES_DIRECTORY "C:/Repositories" CACHE PATH "Path to external libraries")

set(INSTALL_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/target" CACHE PATH "Install directory for project")
set(INSTALL_BINDIR "${INSTALL_DIRECTORY}/bin" CACHE PATH "Install directory for project binaries")
set(INSTALL_LIBDIR "${INSTALL_DIRECTORY}/lib" CACHE PATH "Install directory for project libs")
set(INSTALL_INCLUDEDIR "${INSTALL_DIRECTORY}/include" CACHE PATH "Install directory for project public header")