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

#include "src/Vec2.hpp"


/*
#include <windows.h>
std::string ExePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    return std::string(buffer);
}
*/

/*void Game::init(std::string& fileName, sf::RenderWindow& window, sf::Font& font, std::vector<std::shared_ptr<CShape::CustomShape>>& shapes)
{
    std::vector<std::vector<std::string>> configData;
    Tools::getFileTokens(fileName, configData);
    if(configData.size() < 3)
        throw std::invalid_argument("Error. Not enough arguments in config file.");


    if (configData[0][0] != "Window")
        throw std::invalid_argument("Error. Window data should be at start of config file.");
    uint32_t screenWidth = 0;
    uint32_t screenHeight = 0;
    try
    {
        screenWidth = std::stoi(configData[0][1]);
        screenHeight = std::stoi(configData[0][2]);
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what();
        throw std::invalid_argument("Error. Non valid Window arguments");
    }
    window = sf::RenderWindow(sf::VideoMode({ screenWidth, screenHeight }), "CMake SFML Project");


    if (configData[1][0] != "Fonts")
        throw std::invalid_argument("Error. Fonts data should be second on config file.");
    if (!font.openFromFile(configData[1][1]))
        throw std::invalid_argument("Error. Non valid Font arguments");

    for (int i = 2; i <= configData.size() - 1; ++i)
    {
        shapes.push_back(std::make_shared<CShape::CustomShape>(configData[i], font));
    }
}*/

/*int Game::start()
{
    //std::cout << "my directory is " << ExePath() << "\n";

    //callWindowTest();

    std::string fileName = "config/config.txt";
    sf::RenderWindow window;
    sf::Font font;
    std::vector<std::shared_ptr<CShape::CustomShape>> shapes;
    try
    {
        init(fileName, window, font, shapes);
    }
    catch (std::exception& ex)
    {
        std::cout << "Error by initialization: " << ex.what();
        return -1;
    }

    window.setFramerateLimit(144);
    if (!ImGui::SFML::Init(window))
        return -1;

    CustomGui::FirstGui tst(shapes);

    sf::Clock clock;
    while (window.isOpen())
    {
        ////////// EVENTS ///////////
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // You must create all widgets between ImGui::SFML::Update() and ImGui::Render()
        ImGui::SFML::Update(window, clock.restart());

        ////////// GUI ELEMENTS ///////////
        //ImGui::Begin("Shape Controller");       
        tst.update();
        //ImGui::End();

        
        ////////// Clear window ///////////
        window.clear();

        ////////// PHYSICS ///////////
        for (auto shape : shapes)
        {
            if (shape->isEnabled())
            {
                shape->checkCollisionWindow(window);
                shape->update();
                shape->draw(window);
            }            
        }

        ////////// DRAW CHARACTERS ///////////

        // Draw GUI Elements AFTER SFML so they overlap correctly
        //Don’t call ImGui::Render, only call ImGui::SFML::Render
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}*/


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

