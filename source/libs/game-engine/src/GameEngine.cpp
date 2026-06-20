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
#include "InputCodes.hpp"
#include "actorfactory/ActorType.hpp"
#include "src/general/Random.hpp"
#include "scenes/Action.hpp"
#include "scenes/GeoWarsMainScene.hpp"
#include "scenes/GeoWarsPauseScene.hpp"


namespace GameEngine
{
    GameEngine::GameEngine()
    {   
        init();

        mIsRunning = ImGui::SFML::Init(mWindow);
        if (!mIsRunning)
        {
            std::cout << "ERROR: ImGUI window couldnt be opened." << std::endl;
            return;
        }

        mCurrentScene = std::make_shared<Scene::GeoWarsMainScene>(this);
        mScenes["Main"] = mCurrentScene;
        mCurrenSceneKey = "Main";
        mScenes["Pause"] = std::make_shared<Scene::GeoWarsPauseScene>(this);

        mGuiTools = std::make_unique<GuiTools::ThirdGui>(this, std::dynamic_pointer_cast<Scene::GeoWarsMainScene>(mCurrentScene).get());
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

            // ASSETS
            if (!mFontsData.font.openFromFile(mConfigFile["resources"]["fonts"][0]["file"].get<std::string>()))
                std::cout << "ERROR opening font: " << mConfigFile["fonts"][0]["file"].get<std::string>() << std::endl;
            mFontsData.fontsize = mConfigFile["resources"]["fonts"][0]["size"].get<int>();
            mFontsData.fontcolor = sf::Color(mConfigFile["resources"]["fonts"][0]["color"][0].get<int>(),
                                             mConfigFile["resources"]["fonts"][0]["color"][1].get<int>(),
                                             mConfigFile["resources"]["fonts"][0]["color"][2].get<int>());

            //Textures
            size_t texturesSize = mConfigFile["resources"]["textures"].size();
            for (int i = 0; i < texturesSize; i++)
            {  
                auto textureConfig = mConfigFile["resources"]["textures"][i];
                auto textureName = textureConfig["name"].get<std::string>();
                mTextures[textureName].texture = sf::Texture(textureConfig["file"].get<std::string>());
                mTextures[textureName].size.x = textureConfig["size"][0].get<int>();
                mTextures[textureName].size.y = textureConfig["size"][1].get<int>();

                size_t spritesSize = textureConfig["sprites"].size();
                for (int j = 0; j < spritesSize; j++)
                {
                    auto spriteConfig = textureConfig["sprites"][j];
                    auto spriteName = spriteConfig["name"].get<std::string>();
                    mSprites[spriteName].texture = &mTextures[textureName].texture;
                    mSprites[spriteName].subrect.size.x = spriteConfig["size"][0].get<int>();
                    mSprites[spriteName].subrect.size.y = spriteConfig["size"][1].get<int>();
                    mSprites[spriteName].subrect.position.x = spriteConfig["position"][0].get<int>();
                    mSprites[spriteName].subrect.position.y = spriteConfig["position"][1].get<int>();
                }                
            }

            // PLAYER
            auto playerConfig = mConfigFile["actors"]["player"];
            mActorData.speed = playerConfig["speed"].get<float>();
            mActorData.sprite = playerConfig["sprite"].get<std::string>();
            mActorData.collisionradius = playerConfig["collisionradius"].get<float>();
            mActorData.specialAmount = playerConfig["specialamount"].get<int>();
            mActorData.specialLifespan = playerConfig["speciallifespan"].get<int>();
            mActorData.specialSeparation = playerConfig["specialseparation"].get<int>();
            mActorData.specialCooldown = playerConfig["specialcooldown"].get<int>();

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
        // ImGUI UPDATE
        ImGui::SFML::Update(mWindow, mClock.restart());

        // Gui tool update begin - widgets - end
        mGuiTools->update();

        // Scene Update (systems)
        mCurrentScene->update();
        
    }

    void GameEngine::render()
    {

        mWindow.clear();
        mCurrentScene->sRender();
        // Dra GUI Elements AFTER SFML so they overlap correctly
        //Dont call ImGui::Render, only call ImGui::SFML::Render
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
                processSfmlInput(*event);
            }

            // Update Widgets - Update Scene State(systems, ActorManager)
            update();

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

        mCurrentScene = mScenes[newScene];
        mCurrenSceneKey = newScene;
    }

    void GameEngine::saveScene()
    {
        mCurrentScene->saveScene(mCurrenSceneKey);
    }

    sf::RenderWindow& GameEngine::getWindow()
    {
        return mWindow;
    }

    // Systems    
    void GameEngine::processSfmlInput(const sf::Event& event)
    {
        if (event.is<sf::Event::Closed>())
        {
            mWindow.close();
            mIsRunning = false;
            return;
        }

        if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            sInput(Scene::ActionStateEnum::START, Input::getInputKeyboard(keyPressed->scancode));
        }
        else if (const auto* keyPressed = event.getIf<sf::Event::KeyReleased>())
        {
            sInput(Scene::ActionStateEnum::END, Input::getInputKeyboard(keyPressed->scancode));                
        }
        else if (const auto* buttonPressed = event.getIf<sf::Event::MouseButtonPressed>())
        {
            sInput(Scene::ActionStateEnum::START, Input::getInputMouse(buttonPressed->button));
        }
    }

    void GameEngine::sInput(Scene::ActionStateEnum pActionState, Input::InputCode pInputCode)
    {
        if (mCurrentScene->hasAction(pInputCode))
        {
            Scene::Action action(pActionState, mCurrentScene->getActionType(pInputCode));
            mCurrentScene->doAction(action);
        }
    }  

    const sSpritesData& GameEngine::getSpriteData(std::string& sprite)
    {
        return mSprites[sprite];
    }

}