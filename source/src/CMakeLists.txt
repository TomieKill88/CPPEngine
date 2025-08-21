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

#--------------------------------------------------------------------------
# External Libraries
#--------------------------------------------------------------------------
list(APPEND sfml_LIBRARIES sfml-system 
						 sfml-window 
						 sfml-graphics 
						 sfml-network 
						 sfml-audio)

target_link_libraries(${TARGET_NAME} ${sfml_LIBRARIES})

target_include_directories(${TARGET_NAME} PRIVATE ${sfml_INCLUDEDIR}
												  ${sfml_BINDIR})

#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
install(TARGETS ${TARGET_NAME} 
		DESTINATION ${INSTALL_LIBDIR}
		)

# Only for public libraries that will be used by the app
list(APPEND sfml_PUBLIC_LIBS  #LIBRARIES
							sfml/sfmlTest.hpp
							)

#install(FILES ${sfml_PUBLIC_LIBS}
#		DESTINATION ${INSTALL_INCLUDEDIR}
#		)













