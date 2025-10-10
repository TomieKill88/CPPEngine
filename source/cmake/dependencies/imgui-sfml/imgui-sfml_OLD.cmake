# From https://en.sfml-dev.org/forums/index.php?topic=29201.0
#https://edw.is/using-imgui-with-sfml-pt1/#option-a-using-imgui-sfml-with-cmake
# Had to first build imgui-SFML with: 
# cmake ../ -A "Win32" -DIMGUI_SFML_FIND_SFML=ON -DSFML_DIR="C:\Repositories\SFML-2.6.2\lib\cmake\SFML" -DIMGUI_DIR="C:/Repositories/imgui/" -DBUILD_SHARED_LIBS=OFF
# cmake --build .
# cmake --install . --prefix C:/Repositories/imgui-sfml/bin/Debug --config Debug
# On the imgui-SFML root CmakeLists.txt change required SFML to 2.6.2

# WARNING: you need to add find_package(OpenGL REQUIRED) somewhere in the ImGui-SFMLConfig.cmake or it wont find it!!!

#--------------------------------------------------------------------------
# Find Package
#--------------------------------------------------------------------------
set(TARGET_NAME ImGui-SFML)

# Set ImGui-SFML_DIR for find_package can find sfmlCONFIG.cmake
set(ImGui-SFML_DIR "${imgui-sfml_DIRECTORY}/bin/Debug/lib/cmake/ImGui-SFML")

if (NOT ImGui-SFML_FOUND)
	find_package(${TARGET_NAME} REQUIRED)
endif()

#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
list(APPEND ImGui-SFML_TARGETS ImGui-SFML)

# Only for public libraries that will be used by the app
list(APPEND imgui-sfml_PUBLIC_LIBS  #LIBRARIES
				"${imgui-sfml_DIRECTORY}/bin/Debug/include/imconfig-SFML.h"
				"${imgui-sfml_DIRECTORY}/bin/Debug/include/imgui-SFML.h"
				"${imgui-sfml_DIRECTORY}/bin/Debug/include/imgui-SFML_export.h"
)
						 
install(IMPORTED_RUNTIME_ARTIFACTS ${sfml_TARGETS} 
		DESTINATION ${INSTALL_BINDIR}
		)
		
install(IMPORTED_RUNTIME_ARTIFACTS ${sfml_TARGETS} 
		DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}"
		)
		


install(FILES ${imgui-sfml_PUBLIC_LIBS}
		DESTINATION "${INSTALL_INCLUDEDIR}/imgui-SFML"
		)