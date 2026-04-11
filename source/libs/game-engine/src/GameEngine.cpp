#include <iostream>
#include <memory>
#include <fstream>

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <imgui-SFML.h>
#include <imgui.h>
#include <nlohmann/json.hpp>


#include "GameEngine.hpp"
#include "actorfactory/ActorType.hpp"

using json = nlohmann::json;

namespace GameEngine
{
    GameEngine::GameEngine()
    {   
        // Scene Map
        //mCurrentScene = "BaseScene";
        //Scene::BaseScene baseScene(this);
        //mScenes[mCurrentScene] = baseScene;

        init();

        mIsRunning = ImGui::SFML::Init(mWindow);
        if (!mIsRunning)
        {
            std::cout << "ERROR: ImGUI window couldnt be opened." << std::endl;
            return;
        }

        mGuiTools = std::make_unique<GuiTools::FirstGui>(this);
    }

    void GameEngine::init()
    {
        try
        {
            // Read config file
            std::ifstream f("config/appconfig.json");
            json j = json::parse(f);
            // Set variables and maps
            sf::Vector2u vector;
            vector.x = j["window"]["width"].get<int>();
            vector.y = j["window"]["height"].get<int>();
            mWindow = sf::RenderWindow(sf::VideoMode(vector), "CMake SFML Project");
            mWindow.setFramerateLimit(j["window"]["framerate"].get<int>());


            //TEMP
            sf::Font font;
            if (!font.openFromFile(j["fonts"][0].get<std::string>()))
                std::cout << "ERROR opening font" << std::endl;

            auto shapes = j["actors"]["shapes"];
            size_t actors = shapes.size();

            for (int i = 0; i < actors; i++)
            {
                std::shared_ptr<Actor::Actor> actor = std::make_shared<Actor::Actor>(Actor::ActorTypeEnum::ENEMY, i);
                
                // set position and speed
                actor->add<Components::CTransform>(Tools::Vec2(shapes[i]["x"].get<float>(), shapes[i]["y"].get<float>()), 
                                                    Tools::Vec2(shapes[i]["vx"].get<float>(), shapes[i]["vy"].get<float>()));

                // create shape
                auto& componentShape = actor->add<Components::CShape>(shapes[i]["radius"].get<float>(),
                                                                        font,
                                                                        shapes[i]["vertix"].get<int>());
                // set shape label
                componentShape.mLabel.setString(sf::String(shapes[i]["label"].get<std::string>()));
                componentShape.mLabel.setOrigin(componentShape.mLabel.getLocalBounds().getCenter());

                // set shape color
                componentShape.mShape.setFillColor(sf::Color(shapes[i]["r"].get<int>(), 
                                                             shapes[i]["g"].get<int>(), 
                                                             shapes[i]["b"].get<int>()));
                  
                mActorPool.push_back(actor);
            }           
        }
        catch (std::exception& e)
        {
            std::cout << "ERROR: GameEngine could not be initialized: " << e.what() << std::endl;
        }   
    }

    void GameEngine::update()
    {
        // ImGUI UPDATE
        ImGui::SFML::Update(mWindow, mClock.restart());

        // Gui tool update begin - widgets - end
        mGuiTools->update();
        
        // Scene Update (systems)
        //mScenes[mCurrentScene].update();
        //////////  Wall collision  ///////////////
        for each ( auto& actor in mActorPool)
        {
            auto &transform = actor->get<Components::CTransform>();
            auto &shape = actor->get<Components::CShape>();

            shape.mShape.move(sf::Vector2f{ transform.speed.x, transform.speed.y });
            auto shapeBounds = shape.mShape.getGlobalBounds();
            auto shapeBoundSize = shapeBounds.size;
            auto newPos = shape.mShape.getPosition();
            if ((newPos.x + shapeBoundSize.x) > mWindow.getSize().x || newPos.x < 0.0f)
                transform.speed.x *= -1;
            if ((newPos.y + shapeBoundSize.y) > mWindow.getSize().y || newPos.y < 0.0f)
                transform.speed.y *= -1;
            shape.mLabel.setPosition(shape.mShape.getGlobalBounds().getCenter());
        }        
    }

    void GameEngine::render()
    {
        //Clear window
        mWindow.clear();

        // Draw Scene (render)
        //mScenes[mCurrentScene].render();
        for each (auto & actor in mActorPool)
        {
            auto shape = actor->get<Components::CShape>();

            mWindow.draw(shape.mShape);
            //mWindow.draw(shape.mLabel);
        }

        // Dra GUI Elements AFTER SFML so they overlap correctly
        //Don’t call ImGui::Render, only call ImGui::SFML::Render
        ImGui::SFML::Render(mWindow);

        // Display window buffer
        mWindow.display();
    }

    void GameEngine::run()
    {
        while (mIsRunning)
        {
            // INPUT
            while (const std::optional event = mWindow.pollEvent())
            {
                ImGui::SFML::ProcessEvent(mWindow, *event);

                if (event->is<sf::Event::Closed>())
                {
                    mWindow.close(); 
                    mIsRunning = false;
                }
            }

            // Update Widgets - Update Scene State
            update();

            // Render Widgets - Render Scene State
            render();

        }

        if (mWindow.isOpen())
            mWindow.close();

        ImGui::SFML::Shutdown();
    }

    void GameEngine::quit()
    {
        mIsRunning = false;
    }

    void GameEngine::changeScene(std::string& newScene)
    {
        if (mScenes.find(newScene) == mScenes.end())
        {
            std::cout << "ERROR: " << newScene << " is not an existing scene." << std::endl;
            return;
        }

        mCurrentScene = newScene;

    }

    const sf::RenderWindow& GameEngine::getWindow()
    {
        return mWindow;
    }

    void GameEngine::userInput()
    {}
    
    std::shared_ptr<sf::Shape> getShape(int type)
    {
        if (type == 1)
            return std::make_shared<sf::CircleShape>(30.0f);
        else
            return std::make_shared<sf::RectangleShape>();
    }
        

    ////////////////////////////////////////////////////////////
    /// Entry point of application
    ///
    /// \return Application exit code
    ///
    ////////////////////////////////////////////////////////////
    void drawTest(sf::RenderWindow& window)
    {

        std::shared_ptr<sf::Shape> test = getShape(2);
        auto test2 = *(std::dynamic_pointer_cast<sf::RectangleShape>(test).get());
        test2.setSize({ 50.0, 50.0 });
        window.draw(test2);
    }
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

            ImGui::SameLine(); if (ImGui::Button("Set##Color")) { shape.setFillColor(shapeColor); }


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

    
}