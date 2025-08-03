// A simple program that computes the square root of a number
#include <cmath>
#include <cstdlib> 
#include <iostream>
#include <string>

#include "sfml/sfmlTest.hpp"


int main(int argc, char* argv[])
{
    // convert input to double
    const double inputValue = 99;

    // calculate square root
    const double outputValue = mysqrt(inputValue);
    std::cout << "The square root of " << inputValue << " is " << outputValue
        << std::endl;

    return 0;
}
