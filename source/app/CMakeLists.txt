#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------
set(TARGET_NAME game)
					
add_executable(${TARGET_NAME})

#--------------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------------
list(APPEND game_SOURCES  #sources
						game/game.cpp)

target_sources(${TARGET_NAME} PRIVATE ${game_SOURCES})

#--------------------------------------------------------------------------
# Add libraries
#--------------------------------------------------------------------------
list(APPEND game_LIB_SOURCES 
#OWN
	engine
#EXTERNAL
	#ImGui-SFML::ImGui-SFML
)

target_link_libraries(${TARGET_NAME} PUBLIC ${game_LIB_SOURCES})

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
#target_include_directories(${TARGET_NAME} PUBLIC
#							"${PROJECT_BINARY_DIR}"
#							)

#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
install(TARGETS ${TARGET_NAME}
		DESTINATION ${INSTALL_BINDIR}
)