#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------
set(TARGET_NAME component-factory)
		   
add_library(${TARGET_NAME} STATIC)

#--------------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------------
list(APPEND component_factory_SOURCES  # sources
								src/Component.hpp
								src/CTransform.hpp
								src/CTransform.cpp)

target_sources(${TARGET_NAME} PRIVATE ${component_factory_SOURCES})

#--------------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------------
# State that anybody linking to library needs to include the current source directory
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

#--------------------------------------------------------------------------
# Group Files (mainly for VS)
#--------------------------------------------------------------------------
source_group(src FILES ${component_factory_SOURCES})

#--------------------------------------------------------------------------
# Add Libraries
#--------------------------------------------------------------------------
list(APPEND component_factory_LIBRARIES 
						 helper-tools
						 )

target_link_libraries(${TARGET_NAME} ${component_factory_LIBRARIES})

#--------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------
#install(TARGETS ${TARGET_NAME} 
#		DESTINATION ${INSTALL_LIBDIR}
#		)










