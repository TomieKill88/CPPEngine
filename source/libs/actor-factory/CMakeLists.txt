#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------
set(TARGET_NAME actor-factory)
		   
add_library(${TARGET_NAME} STATIC)

#--------------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------------
list(APPEND actor_factory_SOURCES  # sources
								src/ActorType.hpp
								src/ActorType.cpp
								src/Actor.hpp
								src/Actor.cpp
								src/ActorManager.hpp
								src/ActorManager.cpp
								src/CustomShape.hpp
								src/CustomShape.cpp)

target_sources(${TARGET_NAME} PRIVATE ${actor_factory_SOURCES})

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
# State that anybody linking to library needs to include the current source directory
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

#--------------------------------------------------------------------------
# Group Files (mainly for VS)
#--------------------------------------------------------------------------
source_group(src FILES ${actor_factory_SOURCES})

#--------------------------------------------------------------------------
# External Libraries
#--------------------------------------------------------------------------
list(APPEND actor_factory_LIBRARIES 
						 ImGui-SFML::ImGui-SFML 
						 SFML::Graphics
						 component-factory
						 helper-tools
						 )

target_link_libraries(${TARGET_NAME} ${actor_factory_LIBRARIES})

#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
install(TARGETS ${TARGET_NAME} 
		DESTINATION ${INSTALL_LIBDIR}
		)

# Only for public libraries that will be used by the app
list(APPEND actor_factory_PUBLIC_LIBS  #LIBRARIES
							src/CustomShape.hpp
							)

#install(FILES ${actor_factory_PUBLIC_LIBS}
#		DESTINATION ${INSTALL_INCLUDEDIR}
#		)













