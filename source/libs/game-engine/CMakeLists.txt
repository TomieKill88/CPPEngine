#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------
set(TARGET_NAME game-engine)
		   
add_library(${TARGET_NAME} STATIC)

#--------------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------------
list(APPEND game-engine_SOURCES  # sources
								# Entities								
								src/actorfactory/Components.hpp
								src/actorfactory/Components.cpp
								src/actorfactory/ActorType.hpp
								src/actorfactory/ActorType.cpp
								src/actorfactory/Actor.hpp
								src/actorfactory/Actor.cpp
								src/actorfactory/ActorManager.hpp
								src/actorfactory/ActorManager.cpp
								src/actorfactory/CustomShape.hpp
								src/actorfactory/CustomShape.cpp
								
								# GUI-tools
								src/guitools/BaseGui.hpp
								src/guitools/BaseGui.cpp
								src/guitools/FirstGui.hpp
								src/guitools/FirstGui.cpp
								src/guitools/SecondGui.hpp
								src/guitools/SecondGui.cpp
								
								# Scenes
								src/scenes/BaseScene.hpp
								src/scenes/BaseScene.cpp
								
								# Engine
								src/GameEngine.hpp
								src/GameEngine.cpp
)

target_sources(${TARGET_NAME} PRIVATE ${game-engine_SOURCES})

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
# State that anybody linking to engine needs to include the current source directory
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Add additional include directories.
target_include_directories(${TARGET_NAME}
	PRIVATE		${CMAKE_CURRENT_SOURCE_DIR}/src
	)

#--------------------------------------------------------------------------
# Group Files (mainly for VS)
#--------------------------------------------------------------------------

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src FILES ${game-engine_SOURCES})

#--------------------------------------------------------------------------
# External Libraries
#--------------------------------------------------------------------------
list(APPEND engine_LIBRARIES 
						 helper-tools
						#EXTERNAL
						 ImGui-SFML::ImGui-SFML 
						 SFML::Graphics
						 nlohmann_json::nlohmann_json						 
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
							src/gameengine/engine.hpp
							src/actorfactory/Actor.hpp
							src/components/Component.hpp
							src/actorfactory/ActorManager.hpp
							)

#install(FILES ${sfml_PUBLIC_LIBS}
#		DESTINATION ${INSTALL_INCLUDEDIR}
#		)













