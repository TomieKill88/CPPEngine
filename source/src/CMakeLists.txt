#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------
set(TARGET_NAME engine)
		   
add_library(${TARGET_NAME} STATIC)

#--------------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------------
list(APPEND engine_SOURCES  # sources
								engine/engine.hpp
								engine/engine.cpp)

target_sources(${TARGET_NAME} PRIVATE ${engine_SOURCES})

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
# State that anybody linking to engine needs to include the current source directory
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

#--------------------------------------------------------------------------
# External Libraries
#--------------------------------------------------------------------------
list(APPEND engine_LIBRARIES 
						 #sfml-graphics 
						 ImGui-SFML::ImGui-SFML 
						 SFML::Graphics
						 )

target_link_libraries(${TARGET_NAME} ${engine_LIBRARIES})

#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
install(TARGETS ${TARGET_NAME} 
		DESTINATION ${INSTALL_LIBDIR}
		)

# Only for public libraries that will be used by the app
list(APPEND engine_PUBLIC_LIBS  #LIBRARIES
							engine/engine.hpp
							)

#install(FILES ${sfml_PUBLIC_LIBS}
#		DESTINATION ${INSTALL_INCLUDEDIR}
#		)













