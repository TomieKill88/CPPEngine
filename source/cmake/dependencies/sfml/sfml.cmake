# https://stackoverflow.com/questions/76030829/how-can-i-add-a-non-cmake-library-to-a-cmake-project
#https://gist.github.com/kabasakalis/f05c9c7dba254c93e71c084b8ad3e236
# I already have the compiled binaries for SFML, so I'm just going to create a target
# with that and copy the needed files in /bin and /lib

#--------------------------------------------------------------------------
# Find Package
#--------------------------------------------------------------------------
set(TARGET_NAME SFML)

# SFML_LIB_DIR/cmake/SFML/SFMLConfig.cmake
set(SFML_STATIC_LIBRARIES FALSE)
# Set SFML_DIR for find_package can find sfmlCONFIG.cmake
set(SFML_DIR "${sfml_LIBDIR}/cmake/SFML")

# Gives targets sfml-graphics, sfml-audio, etc for target_link_libraries(myapp sfml-graphics sfml-audio)
if (NOT SFML_FOUND)
	find_package(${TARGET_NAME} REQUIRED system window graphics network audio main)
endif()


#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
# State that anybody linking to sfml needs to include the include directory
#target_include_directories(${TARGET_NAME} INTERFACE ${SFML_INCLUDE_DIR})

#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
list(APPEND sfml_TARGETS sfml-system 
						 sfml-window 
						 sfml-graphics 
						 sfml-network 
						 sfml-audio)
						 
install(IMPORTED_RUNTIME_ARTIFACTS ${sfml_TARGETS} 
		DESTINATION ${INSTALL_BINDIR}
		)
		
install(IMPORTED_RUNTIME_ARTIFACTS ${sfml_TARGETS} 
		DESTINATION "${OUT_DIRECTORY}/Debug"
		)

#message("The debug lib is at " ${SFML_LIB_DIR_DEBUG})


#--------------------------------------------------------------------------
# Add Library
#--------------------------------------------------------------------------
# https://cmake.cmake.narkive.com/m86wIaCe/imported-dll-only-target-on-msvc
#add_library(${TARGET_NAME} SHARED IMPORTED GLOBAL)
#set_target_properties(${TARGET_NAME} 
#						PROPERTIES 
#							INTERFACE_INCLUDE_DIRECTORIES ${SFML_INCLUDE_DIR}
#							IMPORTED_LOCATION ${SFML_BIN_DIR}
#							IMPORTED_IMP_LOCATION ${SFML_LIB_DIR})


