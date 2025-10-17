# https://github.com/SFML/cmake-sfml-project/blob/imgui-sfml/CMakeLists.txt
# https://discourse.cmake.org/t/adding-libraries-from-fetchcontent-to-find-package-lookup/15214/2
#--------------------------------------------------------------------------
# Fetch Package
#--------------------------------------------------------------------------

FetchContent_Declare(ImGui
	GIT_REPOSITORY https://github.com/ocornut/imgui
	GIT_TAG v1.91.1
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM)
	
FetchContent_MakeAvailable(ImGui)

FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)
	