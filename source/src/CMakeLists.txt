#--------------------------------------------------------------------------
# Set Target up
#--------------------------------------------------------------------------

set(sfml_LIBS  sfml/sfmlTest.hpp
			   sfml/sfmlTest.cpp)
			   
add_library(sfmlLib STATIC ${sfml_LIBS})