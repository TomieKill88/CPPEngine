#include <iostream>
#include <memory>
#include <fstream>
#include <random>

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <imgui-SFML.h>
#include <imgui.h>


#include "GameEngine.hpp"
#include "actorfactory/ActorType.hpp"


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
            mConfigFile = nlohmann::json::parse(f);

            // Window
            mWindowData.width = mConfigFile["window"]["width"].get<int>();
            mWindowData.height = mConfigFile["window"]["height"].get<int>();
            mWindowData.framerate = mConfigFile["window"]["framerate"].get<int>();
            mWindowData.fullscreen = mConfigFile["window"]["fullscreen"].get<bool>();
            sf::Vector2u windowSize;
            windowSize.x = mWindowData.width;
            windowSize.y = mWindowData.height;

            auto windowState = sf::State::Windowed;
            if(mConfigFile["window"]["fullscreen"].get<bool>())
                windowState = sf::State::Fullscreen;

            mWindow = sf::RenderWindow(sf::VideoMode(windowSize), "CMake SFML Project", sf::Style::Default, windowState);
            mWindow.setFramerateLimit(mWindowData.framerate);

            // Unique font for component labels
            if (!font.openFromFile(mConfigFile["fonts"][0]["file"].get<std::string>()))
                std::cout << "ERROR opening font" << std::endl;

            // Player
            auto playerConfig = mConfigFile["actors"]["player"];
            auto player = mActorManager.createActor(Actor::ActorTypeEnum::PLAYER);
            // COMPONENT.TRANSFORM
            player->add<Components::CTransform>(Tools::Vec2(windowSize.x/2, windowSize.y/2),
                                                Tools::Vec2(playerConfig["speed"].get<float>(), 
                                                            playerConfig["speed"].get<float>()));

            // COMPONENT.SHAPE
            auto& componentShape = player->add<Components::CShape>(playerConfig["radius"].get<float>(),
                                                                    font,
                                                                    playerConfig["vertices"].get<int>());
            componentShape.mShape.setFillColor(sf::Color(playerConfig["fillcolor"][0].get<int>(),
                                                         playerConfig["fillcolor"][1].get<int>(),
                                                         playerConfig["fillcolor"][2].get<int>()));
            componentShape.mShape.setOutlineColor(sf::Color(playerConfig["oulinecolor"][0].get<int>(),
                                                            playerConfig["oulinecolor"][1].get<int>(),
                                                            playerConfig["oulinecolor"][2].get<int>()));
            componentShape.mShape.setOutlineThickness(playerConfig["oulinethickness"].get<int>());
            componentShape.mShape.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));
            // COMPONENT.SHAPE::label
            componentShape.mLabel.setString(sf::String("player"));
            componentShape.mLabel.setCharacterSize(mConfigFile["fonts"][0]["size"].get<int>());
            componentShape.mLabel.setFillColor(sf::Color(mConfigFile["fonts"][0]["color"][0].get<int>(),
                                                         mConfigFile["fonts"][0]["color"][1].get<int>(),
                                                         mConfigFile["fonts"][0]["color"][2].get<int>()));
            componentShape.mLabel.setOrigin(componentShape.mLabel.getLocalBounds().getCenter());
            // MUST set Font here or else the reference is lost for some reason
            componentShape.mLabel.setFont(componentShape.mFont);

            //COMPONENT.COLLISION
            player->add<Components::CCollision>(playerConfig["collisionradius"].get<float>());

            //COMPONENT.SCORE
            player->add<Components::CScore>(0);

            //COMPONENT.INPUT
            player->add<Components::CInput>(0,0,0,0,0);

            //// BULLETS
            auto bulletConfig = mConfigFile["actors"]["bullets"];
            mBulletData.radius = bulletConfig["radius"].get<float>();
            mBulletData.collisionradius = bulletConfig["collisionradius"].get<float>();
            mBulletData.vertices = bulletConfig["vertices"].get<int>();
            mBulletData.speed = bulletConfig["speed"].get<float>();
            mBulletData.fillcolor = sf::Color(bulletConfig["fillcolor"][0].get<int>(), bulletConfig["fillcolor"][1].get<int>(), bulletConfig["fillcolor"][2].get<int>());
            mBulletData.lifespan = bulletConfig["lifespan"].get<int>();

            //// ENEMIES
            auto enemyConfig = mConfigFile["actors"]["enemies"];
            mEnemyData.radius = enemyConfig["radius"].get<float>();
            mEnemyData.collisionradius = enemyConfig["collisionradius"].get<float>();
            mEnemyData.vertices[0] = enemyConfig["minmaxvertices"][0].get<int>();
            mEnemyData.vertices[1] = enemyConfig["minmaxvertices"][1].get<int>();
            mEnemyData.speed[0] = enemyConfig["minmaxspeed"][0].get<float>();
            mEnemyData.speed[1] = enemyConfig["minmaxspeed"][1].get<float>();
            mEnemyData.outlinecolor = sf::Color(enemyConfig["outlinecolor"][0].get<int>(), enemyConfig["outlinecolor"][1].get<int>(), enemyConfig["outlinecolor"][2].get<int>());
            mEnemyData.outlinethickness = enemyConfig["outlinethickness"].get<int>();
            mEnemyData.lifespanminis = enemyConfig["lifespanminis"].get<int>();
            mEnemyData.spanwinterval = enemyConfig["spawninterval"].get<int>();
        }
        catch (std::exception& e)
        {
            std::cout << "ERROR: GameEngine could not be initialized: " << e.what() << std::endl;
            throw;
        }   
    }

    void GameEngine::update()
    {
        // Update Actors
        mActorManager.update();

        // ImGUI UPDATE
        ImGui::SFML::Update(mWindow, mClock.restart());

        // Gui tool update begin - widgets - end
        mGuiTools->update();
        
        // Scene Update (systems)
        //mScenes[mCurrentScene].update();
        sEnemySpawner();

        auto activeActors = mActorManager.getAllActors();
        for each (auto & active in activeActors)
        {
            auto& actor = mActorManager.getActor(active);

            if (actor->isAlive())
            {
                sMovement(actor);
                sWallCollision(actor);
            }
        }        
    }

    void GameEngine::render()
    {
        //Clear window
        mWindow.clear();

        // Draw Scene (render)
        //mScenes[mCurrentScene].render();
        auto activeActors = mActorManager.getAllActors();
        for each (auto& active in activeActors)
        {
            auto& actor = mActorManager.getActor(active);
            if (actor->isAlive())
            {
                auto& shape = actor->get<Components::CShape>();

                mWindow.draw(shape.mShape);
                mWindow.draw(shape.mLabel);
            }
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

                sInput(*event);                
            }

            // Update Widgets - Update Scene State(systems, ActorManager)
            update();

            // Render Widgets - Render Scene State
            render();

            mFrameCounter++;
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


    // Systems
    void GameEngine::sMovement(ActorManager::ActorPtr actor)
    {        
        auto& transform = actor->get<Components::CTransform>();
        auto& shape = actor->get<Components::CShape>();

        if (actor->has<Components::CInput>())
        {
            auto input = actor->get<Components::CInput>();
            float horizontal = input.mRight - input.mLeft;
            float vertical = input.mDown - input.mUp;

            // "normalize" (1/sqrt(2)) vector if both dir are pressed to keep speed constant
            if (horizontal != 0 && vertical != 0)
            {
                horizontal *= 1/1.4;
                vertical *= 1/1.4;
            }

            shape.mShape.move(sf::Vector2f{ transform.speed.x * horizontal, transform.speed.y * vertical });
        }
        else
        {
            //If actor DOESN'T have CInput component (ENEMY) then move random.
            shape.mShape.move(sf::Vector2f{ transform.speed.x, transform.speed.y });
        }        
        shape.mLabel.setPosition(shape.mShape.getGlobalBounds().getCenter());        
    }

    bool GameEngine::sCollision(ActorManager::ActorPtr mainActor, ActorManager::ActorPtr secondaryActor)
    {
        return false;
    }

    void GameEngine::sWallCollision(ActorManager::ActorPtr actor)
    {   
        // Wall collision
        auto& transform = actor->get<Components::CTransform>();
        auto& shape = actor->get<Components::CShape>();

        auto shapeBounds = shape.mShape.getGlobalBounds();
        auto shapeBoundSize = shapeBounds.size;
        auto newPos = shape.mShape.getPosition();
        if ((newPos.x + shapeBoundSize.x) > mWindow.getSize().x || newPos.x < 0.0f)
            transform.speed.x *= -1;
        if ((newPos.y + shapeBoundSize.y) > mWindow.getSize().y || newPos.y < 0.0f)
            transform.speed.y *= -1;
    }
    
    void GameEngine::sInput(const sf::Event& event)
    {
        if (event.is<sf::Event::Closed>())
        {
            mWindow.close();
            mIsRunning = false;
            return;
        }

        auto players = mActorManager.getActorsOfType(Actor::ActorTypeEnum::PLAYER);
        if (players.empty())
            return;

        auto player = players[0];

        if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::W || keyPressed->scancode == sf::Keyboard::Scancode::Up)
                player->get<Components::CInput>().mUp = 1;
            else if (keyPressed->scancode == sf::Keyboard::Scancode::S || keyPressed->scancode == sf::Keyboard::Scancode::Down)
                player->get<Components::CInput>().mDown = 1;
            else if (keyPressed->scancode == sf::Keyboard::Scancode::A || keyPressed->scancode == sf::Keyboard::Scancode::Left)
                player->get<Components::CInput>().mLeft = 1;
            else if (keyPressed->scancode == sf::Keyboard::Scancode::D || keyPressed->scancode == sf::Keyboard::Scancode::Right)
                player->get<Components::CInput>().mRight = 1;
        }
        else if (const auto* keyPressed = event.getIf<sf::Event::KeyReleased>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::W || keyPressed->scancode == sf::Keyboard::Scancode::Up)
                player->get<Components::CInput>().mUp = 0;
            else if (keyPressed->scancode == sf::Keyboard::Scancode::S || keyPressed->scancode == sf::Keyboard::Scancode::Down)
                player->get<Components::CInput>().mDown = 0;
            else if (keyPressed->scancode == sf::Keyboard::Scancode::A || keyPressed->scancode == sf::Keyboard::Scancode::Left)
                player->get<Components::CInput>().mLeft = 0;
            else if (keyPressed->scancode == sf::Keyboard::Scancode::D || keyPressed->scancode == sf::Keyboard::Scancode::Right)
                player->get<Components::CInput>().mRight = 0;
        }
        else if (const auto* buttonPressed = event.getIf<sf::Event::MouseButtonPressed>())
        {
            if (buttonPressed->button == sf::Mouse::Button::Left)
                player->get<Components::CInput>().mShoot = 1;
        }
        else if (const auto* buttonPressed = event.getIf<sf::Event::MouseButtonReleased>())
        {
            if (buttonPressed->button == sf::Mouse::Button::Left)
                player->get<Components::CInput>().mShoot = 0;
        }
    }

    void GameEngine::sEnemySpawner()
    {
        if (mFrameCounter % mEnemyData.spanwinterval == 0)
        {
            auto enemy = mActorManager.createActor(Actor::ActorTypeEnum::ENEMY);
            // +-50.0 so enemies don't spawn touching the borders
            float x = random<float>(10.0f, (float)(mWindowData.width / 2) - 10.0f);
            float y = random<float>(10.0f, (float)(mWindowData.height / 2) - 10.0f);
            // COMPONENT.TRANSFORM
            float speed = random<float>(mEnemyData.speed[0], mEnemyData.speed[1]);
            enemy->add<Components::CTransform>(Tools::Vec2(x, y),
                Tools::Vec2(speed, speed));

            // COMPONENT.SHAPE
            int v = random<int>(mEnemyData.vertices[0], mEnemyData.vertices[1]);
            auto& componentShape = enemy->add<Components::CShape>(mEnemyData.radius, font, v);
            componentShape.mShape.setFillColor(sf::Color::Black);
            componentShape.mShape.setOutlineColor(mEnemyData.outlinecolor);
            componentShape.mShape.setOutlineThickness(mEnemyData.outlinethickness);
            componentShape.mShape.setPosition(sf::Vector2f(x, y));
            // COMPONENT.SHAPE::label
            componentShape.mLabel.setString(sf::String("enemy"));
            componentShape.mLabel.setCharacterSize(mConfigFile["fonts"][0]["size"].get<int>());
            componentShape.mLabel.setFillColor(sf::Color(mConfigFile["fonts"][0]["color"][0].get<int>(),
                mConfigFile["fonts"][0]["color"][1].get<int>(),
                mConfigFile["fonts"][0]["color"][2].get<int>()));
            componentShape.mLabel.setOrigin(componentShape.mLabel.getLocalBounds().getCenter());
            // MUST set Font here or else the reference is lost for some reason
            componentShape.mLabel.setFont(componentShape.mFont);

            //COMPONENT.COLLISION
            enemy->add<Components::CCollision>(mEnemyData.collisionradius);
        }
    }
    

    ////////////////////////////////////////////////////////////
    /// Entry point of application
    ///
    /// \return Application exit code
    ///
    ////////////////////////////////////////////////////////////
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