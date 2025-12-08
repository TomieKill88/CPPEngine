#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------
set(TARGET_NAME helper-tools)
		   
add_library(${TARGET_NAME} STATIC)

#--------------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------------
list(APPEND helper-tools_SOURCES  # sources
								src/BasicTools.hpp
								src/BasicTools.cpp
								src/ConfigFileReader.hpp
								src/ConfigFileReader.cpp
								src/SmartEnum.hpp
								src/Vec2.hpp)

target_sources(${TARGET_NAME} PRIVATE ${helper-tools_SOURCES})

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
# State that anybody linking to library needs to include the current source directory
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

#--------------------------------------------------------------------------
# Group Files (mainly for VS)
#--------------------------------------------------------------------------

source_group(src FILES ${helper-tools_SOURCES})

#--------------------------------------------------------------------------
# Add Libraries
#--------------------------------------------------------------------------
list(APPEND component_factory_LIBRARIES 
						 SFML::Graphics
						 )


#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
install(TARGETS ${TARGET_NAME} 
		DESTINATION ${INSTALL_LIBDIR}
		)

# Only for public libraries that will be used by the app
#list(APPEND helper-tools_PUBLIC_LIBS  #LIBRARIES
#							src/ConfigFileReader.hpp
#							)

#install(FILES ${sfml_PUBLIC_LIBS}
#		DESTINATION ${INSTALL_INCLUDEDIR}
#		)













