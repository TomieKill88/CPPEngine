# https://github.com/SFML/cmake-sfml-project/blob/imgui-sfml/CMakeLists.txt
# https://discourse.cmake.org/t/adding-libraries-from-fetchcontent-to-find-package-lookup/15214/2
#--------------------------------------------------------------------------
# Fetch Package
#--------------------------------------------------------------------------
FetchContent_Declare(SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 3.0.1
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM	)

FetchContent_MakeAvailable(SFML)	