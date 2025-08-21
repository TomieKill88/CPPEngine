// A simple program that computes the square root of a number
#include <cmath>
#include <cstdlib> 
#include <iostream>
#include <string>

#include "engine/engine.hpp"


#include <windows.h>
#include <string>
#include <iostream>

std::string ExePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    return std::string(buffer);
}


int main(int argc, char* argv[])
{
    // convert input to double
    /*const double inputValue = 99;

    // calculate square root
    const double outputValue = mysqrt(inputValue);
    std::cout << "The square root of " << inputValue << " is " << outputValue
        << std::endl;*/

    std::cout << "my directory is " << ExePath() << "\n";

    callWindowTest();

    return 0;
}
