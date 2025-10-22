// A simple program that computes the square root of a number
#include <cmath>
#include <cstdlib> 
#include <iostream>
#include <string>

#include "src/engine.hpp"
#include "src/ConfigFileReader.hpp"


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
    std::cout << "my directory is " << ExePath() << "\n";

    //callWindowTest();

    std::string fileName = "config/config.txt";
    std::vector<std::vector<std::string>> tokens;

    ConfigFileReader::getFileTokens(fileName, tokens);

    return 0;
}
