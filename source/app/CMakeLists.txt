#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------
list(APPEND app_SOURCES  sfml/cppapp.cpp)
					
add_executable(CppApp ${app_SOURCES})

#--------------------------------------------------------------------------
# Add libraries
#--------------------------------------------------------------------------
# OWN
list(APPEND SFML_LIBS sfmlLib)

target_link_libraries(CppApp PUBLIC ${SFML_LIBS})

# EXTERNAL

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
target_include_directories(CppApp PUBLIC
							"${PROJECT_BINARY_DIR}"
							"${LIBRARIES_DIRECTORY}"
							)							