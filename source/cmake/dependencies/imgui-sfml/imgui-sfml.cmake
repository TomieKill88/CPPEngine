# https://github.com/SFML/cmake-sfml-project/blob/imgui-sfml/CMakeLists.txt
# https://discourse.cmake.org/t/adding-libraries-from-fetchcontent-to-find-package-lookup/15214/2
#--------------------------------------------------------------------------
# Fetch Package
#--------------------------------------------------------------------------

set(IMGUI_SFML_FIND_SFML OFF)

FetchContent_Declare(ImGui-SFML
	GIT_REPOSITORY https://github.com/SFML/imgui-sfml
	GIT_TAG v3.0
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM)
	
FetchContent_MakeAvailable(ImGui-SFML)