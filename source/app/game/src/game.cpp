#include <cstdlib> 
#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "Game.hpp"
#include "src/ActorType.hpp"
#include "src/BasicTools.hpp"
#include "src/ConfigFileReader.hpp"
#include "src/engine.hpp"
#include "src/FirstGui.hpp"
#include "src/GeoWarsGUI.hpp"
#include "src/Vec2.hpp"

/*
#include <windows.h>
std::string ExePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    return std::string(buffer);
}
*/

void Game::spawnPlayer()
{
    if (player)
    {
        std::cout << "Player already created;";
        return;
    }
        
    player = actorManager.createActor(Actor::ActorTypeEnum::PLAYER);
    player->add<Component::CShape>(playerData.radius, playerData.fillColor, playerData.outlineColor, playerData.lineThickness, playerData.vertices);
    player->add<Component::CTransform>(Tools::Vec2f{0.0, 0.0}, Tools::Vec2f{playerData.speed, playerData.speed}, Tools::Vec2f{ 1.0, 1.0 }, 10.0);
    player->add<Component::CCollision>(playerData.collisionRadius);
    player->add<Component::CInput>();
    player->add<Component::CScore>();
}

void Game::spawnEnemy()
{
    Actor::ActorPtr tmpEnemy = actorManager.createActor(Actor::ActorTypeEnum::ENEMY);
    tmpEnemy->add<Component::CShape>(enemyData.radius, sf::Color::Black, enemyData.outlineColor, enemyData.lineThickness, enemyData.maxVertices);
    tmpEnemy->add<Component::CTransform>(Tools::Vec2f{ Tools::getRandomFloat(10.0, 200), Tools::getRandomFloat(10.0, 200) }, Tools::Vec2f{ Tools::getRandomFloat(1.0, enemyData.maxSpeed), Tools::getRandomFloat(1.0, enemyData.maxSpeed) }, Tools::Vec2f{ 1.0, 1.0 }, 10.0);
    tmpEnemy->add<Component::CCollision>(enemyData.collisionRadius);
}

void Game::spawnBullet()
{
    Actor::ActorPtr tmpBullet = actorManager.createActor(Actor::ActorTypeEnum::BULLET);
    tmpBullet->add<Component::CShape>(bulletData.radius, bulletData.fillColor, bulletData.fillColor, 0, bulletData.vertices);

    auto pos = player->get<Component::CShape>();
    tmpBullet->add<Component::CTransform>(Tools::Vec2f{pos.shape.getPosition()}, Tools::Vec2f(bulletData.speed, bulletData.speed), Tools::Vec2f{ 1.0, 1.0 }, 0.0);
    tmpBullet->add<Component::CCollision>(bulletData.collisionRadius);
    tmpBullet->add<Component::CLifeSpawn>(bulletData.lifeSpan);
}

void Game::readConfiguration(std::string& fileName)
{
    Tools::seed();

    playerData.radius = 5;
    playerData.collisionRadius = 5;
    playerData.speed = 5.0;
    playerData.fillColor = sf::Color(0, 0, 255);
    playerData.outlineColor = sf::Color(255, 255, 255);
    playerData.lineThickness = 1;
    playerData.vertices = 10;

    enemyData.radius = 5;
    enemyData.collisionRadius = 5;
    enemyData.minSpeed = 3.0;
    enemyData.maxSpeed = 8.0;
    enemyData.outlineColor = sf::Color(255, 0, 0);
    enemyData.lineThickness = 2;
    enemyData.maxVertices = 6;
    enemyData.lifeSpan = 5;
    enemyData.spawnInterval = 30;
    
    bulletData.radius = 1;
    bulletData.collisionRadius = 1;
    bulletData.speed = 4.0f;
    bulletData.fillColor = sf::Color(255, 255, 255);
    bulletData.vertices = 8;
    bulletData.lifeSpan = 600;
}

void Game::init(std::string& fileName)
{
    /*std::vector<std::vector<std::string>> configData;
    Tools::getFileTokens(fileName, configData);
    if(configData.size() < 3)
        throw std::invalid_argument("Error. Not enough arguments in config file.");*/

    readConfiguration(fileName);

    uint32_t screenWidth = 640;
    uint32_t screenHeight = 480;
    window = sf::RenderWindow(sf::VideoMode({ screenWidth, screenHeight }), "HW2: Geometry wars");


    // Load Assets
    if (!font.openFromFile("resources/AovelSans.ttf"))
        throw std::invalid_argument("Error. Non valid Font arguments");

}

int Game::start()
{
    window.setFramerateLimit(144);
    window.setKeyRepeatEnabled(false);
    if (!ImGui::SFML::Init(window))
        return -1;

    CustomGui::GeoWarsGUI gui(actorManager);

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
        gui.update();


        ////////// Clear window ///////////
        window.clear();

        ////////// PHYSICS ///////////
        /*for (auto shape : shapes)
        {
            if (shape->isEnabled())
            {
                shape->checkCollisionWindow(window);
                shape->update();
                shape->draw(window);
            }
        }*/

        ////////// DRAW CHARACTERS ///////////

        // Draw GUI Elements AFTER SFML so they overlap correctly
        //Don’t call ImGui::Render, only call ImGui::SFML::Render
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

sf::RenderWindow& Game::getWindow()
{
    return window;
}

Actor::ActorManager& Game::getActorManager()
{ 
    return actorManager;
}

/*int Game::start_OLD()
{
    //std::cout << "my directory is " << ExePath() << "\n";

    //callWindowTest();

    std::string fileName = "config/config.txt";
    sf::RenderWindow window;
    sf::Font font;
    std::vector<std::shared_ptr<CShape::CustomShape>> shapes;
    try
    {
        //init(fileName, window, font, shapes);
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
