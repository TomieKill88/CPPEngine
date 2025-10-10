# https://github.com/SFML/cmake-sfml-project/blob/imgui-sfml/CMakeLists.txt

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