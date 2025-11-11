#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------
set(TARGET_NAME game)
					
add_executable(${TARGET_NAME})

#--------------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------------
list(APPEND game_SOURCES  #sources
						src/game.cpp)

target_sources(${TARGET_NAME} PRIVATE ${game_SOURCES})

#--------------------------------------------------------------------------
# Add libraries
#--------------------------------------------------------------------------
list(APPEND game_LIB_SOURCES 
#OWN
	engine
	helper-tools
	actor-factory
#EXTERNAL
	ImGui-SFML::ImGui-SFML 
	SFML::Graphics
)

target_link_libraries(${TARGET_NAME} PUBLIC ${game_LIB_SOURCES})

#--------------------------------------------------------------------------
# Group Files (mainly for VS)
#--------------------------------------------------------------------------
source_group(src FILES ${game_SOURCES})

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
#target_include_directories(${TARGET_NAME} PUBLIC
#							"${PROJECT_BINARY_DIR}"
#							)

#--------------------------------------------------------------------------
# Target Properties
#--------------------------------------------------------------------------
#https://stackoverflow.com/questions/47244633/set-visual-studio-debugger-working-directory-to-executable-output-directory-in-c
# Ensures that the debugger can find the resources and config directories
if(MSVC)
	set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${OUT_DIRECTORY}/bin")
endif()

#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
install(TARGETS ${TARGET_NAME}
		DESTINATION ${INSTALL_BINDIR}
)