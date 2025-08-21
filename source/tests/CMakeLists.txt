# https://google.github.io/googletest/quickstart-cmake.html
# https://pikotutorial.com/build-run-c-unit-tests-with-cmake/

#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------
enable_testing()

set(UNIT_TEST_TARGET_NAME unittests)

add_executable(${UNIT_TEST_TARGET_NAME})

#--------------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------------
target_sources(${UNIT_TEST_TARGET_NAME} PRIVATE 
    src/tests.cpp
)

#--------------------------------------------------------------------------
# Add libraries
#--------------------------------------------------------------------------
target_link_libraries(${UNIT_TEST_TARGET_NAME} PRIVATE 
#OWN
	engine
#EXTERNAL
	GTest::gtest_main
)

target_include_directories(${UNIT_TEST_TARGET_NAME} PRIVATE ${sfml_INCLUDEDIR}
															${LIBRARIES_DIRECTORY})

#--------------------------------------------------------------------------
# Add Tests
#--------------------------------------------------------------------------
add_test(NAME ${UNIT_TEST_TARGET_NAME} COMMAND ${UNIT_TEST_TARGET_NAME})
