#--------------------------------------------------------------------------
# Set Target Name
#--------------------------------------------------------------------------
set(TARGET_NAME imgui-SFML)

add_library(${TARGET_NAME} STATIC)

#--------------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------------

list(APPEND imgui-sfml_SOURCES  
	"${imgui-sfml_DIRECTORY}/imconfig-SFML.h"
    "${imgui-sfml_DIRECTORY}/imgui-SFML.cpp"
    "${imgui-sfml_DIRECTORY}/imgui-SFML.h"
    "${imgui-sfml_DIRECTORY}/imgui-SFML_export.h"
)

target_sources(${TARGET_NAME} PRIVATE ${imgui-sfml_SOURCES})

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
# State that anybody linking to imgui needs to include its source directory
target_include_directories(${TARGET_NAME} INTERFACE ${imgui-sfml_DIRECTORY})

#--------------------------------------------------------------------------
# Add libraries
#--------------------------------------------------------------------------
list(APPEND imgui-sfml_LIB_SOURCES 
	sfml-graphics
	imgui
)

target_link_libraries(${TARGET_NAME} PUBLIC ${imgui-sfml_LIB_SOURCES})

target_include_directories(${TARGET_NAME} PRIVATE ${imgui_DIRECTORY})

#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
install(TARGETS ${TARGET_NAME} 
		DESTINATION ${INSTALL_LIBDIR}
		)