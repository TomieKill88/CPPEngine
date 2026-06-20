#include <cstdlib> 
#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "Game.hpp"
#include "src/GameEngine.hpp"

#include "src/science/Vec2.hpp"


/*
#include <windows.h>
std::string ExePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    return std::string(buffer);
}
*/

int Game::start()
{
    //std::cout << "my directory is " << ExePath() << "\n";


    std::cout << "Start game" << std::endl;

    try
    {
        GameEngine::GameEngine mGameEngine;
        mGameEngine.run();
    }
    catch (std::exception& e)
    {
        std::cout << "Execution stopped: " << e.what() << std::endl;
    }

    return 0;
}

