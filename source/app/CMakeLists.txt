#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------
set(app_SOURCES  sfml/cppapp.cpp)
					
add_executable(CppApp ${app_SOURCES})

#--------------------------------------------------------------------------
# Add libraries
#--------------------------------------------------------------------------
# OWN
target_link_libraries(CppApp PUBLIC sfmlLib)

# EXTERNAL

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
target_include_directories(CppApp PUBLIC
							"${PROJECT_BINARY_DIR}"
							"${PROJECT_SOURCE_DIR}/src"
							)
							
message(DEBUG ${PROJECT_SOURCE_DIR})