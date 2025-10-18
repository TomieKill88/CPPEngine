#include <iostream>

#include "engine.hpp"

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
void callWindowTest()
{    
    uint32_t screenWidth = 640;
    uint32_t screenHeight = 480;
    auto window = sf::RenderWindow(sf::VideoMode({ screenWidth, screenHeight }), "CMake SFML Project");
    window.setFramerateLimit(144);

    if (!ImGui::SFML::Init(window))
        return;

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    float speedX = 1.0f;
    float speedY = 1.0f;

    sf::Font font("resources/AovelSans.ttf");
    sf::Text label(font);

    // set the string to display
    label.setString("Pelota");
    // set the character size in pixels
    label.setCharacterSize(24); 
    //Set origin point to center of label
    label.setOrigin(label.getLocalBounds().getCenter());

    sf::Clock clock;
    while (window.isOpen())
    {
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


        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        window.clear();

        shape.move(sf::Vector2f{ speedX,speedY });

        auto shapeBounds = shape.getGlobalBounds();
        auto shapeBoundSize = shapeBounds.size;

        auto newPos = shape.getPosition();
        if ((newPos.x + shapeBoundSize.x) > window.getSize().x || newPos.x < 0.0f)
            speedX *= -1;
        if ((newPos.y + shapeBoundSize.y) > window.getSize().y || newPos.y < 0.0f)
            speedY *= -1;

        label.setPosition(shape.getGlobalBounds().getCenter());

        //Draw here
        window.draw(shape);
        window.draw(label);

        // Dra GUI Elements AFTER SFML so they overlap correctly
        //Don’t call ImGui::Render, only call ImGui::SFML::Render
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
}