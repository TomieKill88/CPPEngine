#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------
set(TARGET_NAME config-file-reader)
		   
add_library(${TARGET_NAME} STATIC)

#--------------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------------
list(APPEND reader_SOURCES  # sources
								src/ConfigFileReader.hpp
								src/ConfigFileReader.cpp)

target_sources(${TARGET_NAME} PRIVATE ${reader_SOURCES})

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
# State that anybody linking to library needs to include the current source directory
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

#--------------------------------------------------------------------------
# Group Files (mainly for VS)
#--------------------------------------------------------------------------

source_group(src FILES ${reader_SOURCES})

#--------------------------------------------------------------------------
# External Libraries
#--------------------------------------------------------------------------


#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
install(TARGETS ${TARGET_NAME} 
		DESTINATION ${INSTALL_LIBDIR}
		)

# Only for public libraries that will be used by the app
list(APPEND reader_PUBLIC_LIBS  #LIBRARIES
							src/ConfigFileReader.hpp
							)

#install(FILES ${sfml_PUBLIC_LIBS}
#		DESTINATION ${INSTALL_INCLUDEDIR}
#		)













