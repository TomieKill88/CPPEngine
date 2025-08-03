#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------

list(APPEND sfml_LIBS  sfml/sfmlTest.hpp
					   sfml/sfmlTest.cpp)
			   
add_library(sfmlLib STATIC ${sfml_LIBS})