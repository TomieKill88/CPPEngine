#include <iostream>
#include <memory>

#include "engine.hpp"

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>


std::shared_ptr<sf::Shape> getShape(int type)
{    
    if (type == 1)
        return std::make_shared<sf::CircleShape>(30.0f);
    else
        return std::make_shared<sf::RectangleShape>();
}

void drawTest(sf::RenderWindow& window)
{

    std::shared_ptr<sf::Shape> test = getShape(2);
    auto test2 = *(std::dynamic_pointer_cast<sf::RectangleShape>(test).get());
    test2.setSize({ 50.0, 50.0 });
    window.draw(test2);
}

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

    // Variables for widgets
    char nameInput[100] = "";
    int inputR = 0, inputG = 0, inputB = 0;

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


        ImGui::Begin("Shape Controller");

        //////////  Shape name  ///////////////

        ImGui::InputTextWithHint("Name", "Enter shape name", nameInput, IM_ARRAYSIZE(nameInput));
        ImGui::SameLine(); if (ImGui::Button("Set"))
        {
            label.setString(sf::String(nameInput));
            label.setOrigin(label.getLocalBounds().getCenter());
        }

        //////////  Shape size  ///////////////

        float radius = shape.getRadius();
        ImGui::SliderFloat("Radius", &radius, 1.0f, 200.0f, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp);
        shape.setRadius(radius);
        //////////  Shape Color  ///////////////
        sf::Color shapeColor;
        // Set width of next widget (popItemWidth to revert)
        ImGui::PushItemWidth(30);
        // Put 0 in step so there are no buttons
        ImGui::InputInt("R", &inputR, 0);
        if (inputR < 0) inputR = 0;
        if (inputR > 255) inputR = 255;
        shapeColor.r = static_cast<uint8_t>(inputR);

        ImGui::SameLine();
        // Set width of next widget (popItemWidth to revert)
        ImGui::PushItemWidth(30);
        // Put 0 in step so there are no buttons
        ImGui::InputInt("G", &inputG, 0);
        if (inputG < 0) inputG = 0;
        if (inputG > 255) inputG = 255;
        shapeColor.g = static_cast<uint8_t>(inputG);

        ImGui::SameLine();
        // Set width of next widget (popItemWidth to revert)
        ImGui::PushItemWidth(30);
        // Put 0 in step so there are no buttons
        ImGui::InputInt("B", &inputB, 0);
        if (inputB < 0) inputB = 0;
        if (inputB > 255) inputB = 255;
        shapeColor.b = static_cast<uint8_t>(inputB);

        ImGui::SameLine(); if (ImGui::Button("Set##Color")){ shape.setFillColor(shapeColor); }
        

        ImGui::End();

        window.clear();

        //////////  Wall collision  ///////////////

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

        drawTest(window);

        // Dra GUI Elements AFTER SFML so they overlap correctly
        //Don’t call ImGui::Render, only call ImGui::SFML::Render
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
}