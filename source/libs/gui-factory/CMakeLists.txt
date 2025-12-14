#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------
set(TARGET_NAME gui-factory)
		   
add_library(${TARGET_NAME} STATIC)

#--------------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------------
list(APPEND gui_factory_SOURCES  # sources
								src/BaseGui.hpp
								src/BaseGui.cpp
								src/FirstGui.hpp
								src/FirstGui.cpp
								src/GeoWarsGUI.hpp
								src/GeoWarsGUI.cpp)

target_sources(${TARGET_NAME} PRIVATE ${gui_factory_SOURCES})

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
# State that anybody linking to library needs to include the current source directory
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

#--------------------------------------------------------------------------
# Group Files (mainly for VS)
#--------------------------------------------------------------------------
source_group(src FILES ${gui_factory_SOURCES})

#--------------------------------------------------------------------------
# External Libraries
#--------------------------------------------------------------------------
list(APPEND gui_factory_LIBRARIES
#OWN
	actor-factory
#EXTERNAL
	ImGui-SFML::ImGui-SFML 
	SFML::Graphics
)

target_link_libraries(${TARGET_NAME} ${gui_factory_LIBRARIES})

#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
install(TARGETS ${TARGET_NAME} 
		DESTINATION ${INSTALL_LIBDIR}
		)

# Only for public libraries that will be used by the app
list(APPEND gui_factory_PUBLIC_LIBS  #LIBRARIES
							src/FirstGui.hpp
							)

#install(FILES ${gui_factory_PUBLIC_LIBS}
#		DESTINATION ${INSTALL_INCLUDEDIR}
#		)













