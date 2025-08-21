#--------------------------------------------------------------------------
# Set Target Name
#--------------------------------------------------------------------------
set(TARGET_NAME imgui)

add_library(${TARGET_NAME} STATIC)

#--------------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------------

list(APPEND imgui_SOURCES  
	"${imgui_DIRECTORY}/imgui.h"
    "${imgui_DIRECTORY}/imgui.cpp"
    "${imgui_DIRECTORY}/imconfig.h"
    "${imgui_DIRECTORY}/imgui_demo.cpp"
    "${imgui_DIRECTORY}/imgui_draw.cpp"
    "${imgui_DIRECTORY}/imgui_internal.h"
    "${imgui_DIRECTORY}/imstb_rectpack.h"
    "${imgui_DIRECTORY}/imstb_textedit.h"
    "${imgui_DIRECTORY}/imstb_truetype.h"
    "${imgui_DIRECTORY}/imgui_tables.cpp"
    "${imgui_DIRECTORY}/imgui_widgets.cpp"
)

target_sources(${TARGET_NAME} PRIVATE ${imgui_SOURCES})

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
# State that anybody linking to imgui needs to include its source directory
target_include_directories(${TARGET_NAME} INTERFACE ${imgui_DIRECTORY})

#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
install(TARGETS ${TARGET_NAME} 
		DESTINATION ${INSTALL_LIBDIR}
		)

# Only for public libraries that will be used by the app
list(APPEND imgui_PUBLIC_LIBS  #LIBRARIES
	"${imgui_DIRECTORY}/imgui.h"
	"${imgui_DIRECTORY}/imconfig.h"
	"${imgui_DIRECTORY}/imgui_internal.h"
    "${imgui_DIRECTORY}/imstb_rectpack.h"
    "${imgui_DIRECTORY}/imstb_textedit.h"
    "${imgui_DIRECTORY}/imstb_truetype.h"							
							)

#install(FILES ${imgui_PUBLIC_LIBS}
#		DESTINATION ${INSTALL_INCLUDEDIR}
#		)