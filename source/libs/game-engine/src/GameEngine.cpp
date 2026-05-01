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
#include "src/general/Random.hpp"


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

        mGuiTools = std::make_unique<GuiTools::SecondGui>(this);
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
            mActorData.speed = playerConfig["speed"].get<float>();
            player->add<Components::CTransform>(Tools::Science::Vec2(windowSize.x/2, windowSize.y/2),
                                                Tools::Science::Vec2(mActorData.speed, mActorData.speed));

            // COMPONENT.SHAPE
            mActorData.radius = playerConfig["radius"].get<float>();
            mActorData.vertices = playerConfig["vertices"].get<int>();
            mActorData.fillcolor = sf::Color(playerConfig["fillcolor"][0].get<int>(),
                                            playerConfig["fillcolor"][1].get<int>(),
                                            playerConfig["fillcolor"][2].get<int>());
            mActorData.outlinecolor = sf::Color(playerConfig["oulinecolor"][0].get<int>(),
                                                playerConfig["oulinecolor"][1].get<int>(),
                                                playerConfig["oulinecolor"][2].get<int>());
            mActorData.outlinethickness = playerConfig["oulinethickness"].get<int>();
            mActorData.collisionradius = playerConfig["collisionradius"].get<float>();
            mActorData.specialAmount = playerConfig["specialamount"].get<int>();
            mActorData.specialLifespan = playerConfig["speciallifespan"].get<int>();
            mActorData.specialSeparation = playerConfig["specialseparation"].get<int>();
            mActorData.specialCooldown = playerConfig["specialcooldown"].get<int>();

            auto& componentShape = player->add<Components::CShape>(mActorData.radius, font, mActorData.vertices);
            componentShape.mShape.setFillColor(mActorData.fillcolor);
            componentShape.mShape.setOutlineColor(mActorData.outlinecolor);
            componentShape.mShape.setOutlineThickness(mActorData.outlinethickness);
            componentShape.mShape.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));
            // COMPONENT.SHAPE::label
            componentShape.mLabel.setString(sf::String(""));
            componentShape.mLabel.setCharacterSize(mConfigFile["fonts"][0]["size"].get<int>());
            componentShape.mLabel.setFillColor(sf::Color(mConfigFile["fonts"][0]["color"][0].get<int>(),
                                                         mConfigFile["fonts"][0]["color"][1].get<int>(),
                                                         mConfigFile["fonts"][0]["color"][2].get<int>()));
            componentShape.mLabel.setOrigin(componentShape.mLabel.getLocalBounds().getCenter());
            // MUST set Font here or else the reference is lost for some reason
            componentShape.mLabel.setFont(componentShape.mFont);

            //COMPONENT.COLLISION
            player->add<Components::CCollision>(mActorData.collisionradius);

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
                
        auto player = mActorManager.getActor(Actor::ActorTypeEnum::PLAYER, 0);
        auto enemies = mActorManager.getActorsOfType(Actor::ActorTypeEnum::ENEMY);
        auto minis = mActorManager.getActorsOfType(Actor::ActorTypeEnum::ENEMY_MINI);
        auto bullets = mActorManager.getActorsOfType(Actor::ActorTypeEnum::BULLET);
        auto shields = mActorManager.getActorsOfType(Actor::ActorTypeEnum::SHIELD);

        // PLAYER 
        if (player->get<Components::CInput>().mShoot)
            sShoot(player); // Only the player shoots at the moment.
        if (invincible >= 0)
            sInvincibility(player);
        if (specials > 0)
            sSpecial(player);

        // ENEMY COLLISIONS
        for each (auto & enemy in enemies)
        {
            if (!enemy->isAlive())
                continue;

            // Check if player should be invincible
            if (invincible <= 0)
            {
                if (sCollision(player, enemy))
                {
                    auto spawnPos = player->get<Components::CTransform>().position;
                    player->get<Components::CShape>().mShape.setPosition(sf::Vector2f(spawnPos.x, spawnPos.y));
                    mActorManager.destroyActor(enemy->getId());
                    invincible = INVINCIBILITY_FRAMES;
                    activeEnemies -= 1;
                    continue;
                }
            }            

            for each (auto & bullet in bullets)
            {
                if (!bullet->isAlive())
                    continue;
               
                if (sCollision(enemy, bullet))
                {
                    sSmallEnemySpawner(enemy);
                    mActorManager.destroyActor(enemy->getId());
                    mActorManager.destroyActor(bullet->getId());
                    activeEnemies -= 1;
                    break; // break because enemy was destroyed, no need to check with any other bullet
                }               
            }

            for each(auto shield in shields)
            {
                if (sCollision(enemy, shield))
                {
                    std::cout << "COLLISION!: " << shield->getTagString() << " " << enemy->getTagString() << std::endl;
                    enemy->get<Components::CTransform>().speed.x *= -1;
                    enemy->get<Components::CTransform>().speed.y *= -1;
                    shield->remove<Components::CCollision>();
                    break;
                }
            }
        }

        for each (auto & mini in minis)
        {
            if (!mini->isAlive())
                continue;

            // Check if player should be invincible
            if (invincible <= 0)
            {
                if (sCollision(player, mini))
                {
                    auto spawnPos = player->get<Components::CTransform>().position;
                    player->get<Components::CShape>().mShape.setPosition(sf::Vector2f(spawnPos.x, spawnPos.y));
                    mActorManager.destroyActor(mini->getId());
                    invincible = INVINCIBILITY_FRAMES;
                    continue;
                }
            }

            for each (auto & bullet in bullets)
            {
                if (!bullet->isAlive())
                    continue;
                
                if (sCollision(mini, bullet))
                {
                    mActorManager.destroyActor(mini->getId());
                    mActorManager.destroyActor(bullet->getId());
                    break; // break because bullet was destroyed, no need to check with any other enemy
                }
            }        
        }

        
        // MOVEMENT & WALLCOLLISION & LIFESPAN
        auto activeActorIndex = mActorManager.getAllActors();
        for each (auto active in activeActorIndex)
        {
            auto& actor = mActorManager.getActor(active);

            if (!actor->isAlive())
                continue;

            if (actor->has<Components::CLifespan>())
            {                
                int initial = actor->get<Components::CLifespan>().mLifeFrames;
                actor->get<Components::CLifespan>().mRemainingFrames -= 1;
                int remain = actor->get<Components::CLifespan>().mRemainingFrames;
                sf::Color color = actor->get<Components::CShape>().mShape.getFillColor();
                sf::Color out = actor->get<Components::CShape>().mShape.getOutlineColor();
                if(actor->getTag() != Actor::ActorTypeEnum::SHIELD)
                    color.a = 255 * ((float)remain / initial);
                out.a = 255 * ((float)remain / initial);
                actor->get<Components::CShape>().mShape.setFillColor(color);
                actor->get<Components::CShape>().mShape.setOutlineColor(out);
                if (remain <= 0)
                {
                    mActorManager.destroyActor(actor->getId());
                    continue;
                }

            }

            if (actor->getTag() == Actor::ActorTypeEnum::SHIELD)
            {
                auto& shape = actor->get<Components::CShape>().mShape;
                shape.setPosition(player->get<Components::CShape>().mShape.getPosition());
            }

            sMovement(actor);
            sWallCollision(actor);            
        }

        sEnemySpawner();
        if(invincible > 0)
            invincible--;
        if (cooldown > 0)
        {
            cooldown--;
            int timeToRepeat = cooldown / 60;
            player->get<Components::CShape>().mLabel.setString(sf::String(std::to_string(timeToRepeat).c_str()));
        }
        else
        {
            player->get<Components::CShape>().mLabel.setString(sf::String(""));
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

                //for debugging
                auto& coll= actor->get<Components::CCollision>();
                if(coll.mDraw)
                {
                    coll.mShape.setPosition(shape.mShape.getPosition());
                    mWindow.draw(coll.mShape);
                }
            }
        }

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
        auto type = actor->getTag();
        auto& transform = actor->get<Components::CTransform>();
        auto& shape = actor->get<Components::CShape>();

        if (actor->has<Components::CInput>())
        {
            auto input = actor->get<Components::CInput>();
            float horizontal = input.mRight - input.mLeft;
            float vertical = input.mDown - input.mUp;

            // "normalize" (1/sqrt(2)) = 1/1.4 = 0.714 vector if both dir are pressed to keep speed constant
            if (horizontal != 0 && vertical != 0)
            {
                horizontal *= 0.714;
                vertical *= 0.714;
            }

            shape.mShape.move(sf::Vector2f{ transform.speed.x * horizontal, transform.speed.y * vertical });
        }
        else
        {
            shape.mShape.move(sf::Vector2f{ transform.speed.x, transform.speed.y });
        }        
        shape.mLabel.setPosition(shape.mShape.getGlobalBounds().getCenter());

        // player is done. Only enemies rotate
        if (type == Actor::ActorTypeEnum::PLAYER || type == Actor::ActorTypeEnum::SHIELD)
            return;        

        shape.mShape.rotate(sf::degrees(5));
    }

    bool GameEngine::sCollision(ActorManager::ActorPtr mainActor, ActorManager::ActorPtr secondaryActor)
    {
        if (!mainActor->has<Components::CCollision>() || !secondaryActor->has<Components::CCollision>())
            return false;

        float mainRadius = mainActor->get<Components::CCollision>().mRadius;
        float secondRadius = secondaryActor->get<Components::CCollision>().mRadius;

        auto mainActorPos = mainActor->get<Components::CShape>().mShape.getPosition();
        auto secondActorPos = secondaryActor->get<Components::CShape>().mShape.getPosition();

        float distSquared = (secondActorPos.x - mainActorPos.x) * (secondActorPos.x - mainActorPos.x) +
                            (secondActorPos.y - mainActorPos.y) * (secondActorPos.y - mainActorPos.y);
        
        return  distSquared < (mainRadius + secondRadius)* (mainRadius + secondRadius);
    }

    void GameEngine::sWallCollision(ActorManager::ActorPtr actor)
    {   
        if (!actor->has<Components::CCollision>())
            return;

        // Wall collision
        float actorRadiusSquared = actor->get<Components::CCollision>().mRadius;
        actorRadiusSquared *= actorRadiusSquared;
        auto& transform = actor->get<Components::CTransform>();
        auto& shape = actor->get<Components::CShape>();
        auto pos = shape.mShape.getPosition();

        if (actor->getTag() == Actor::ActorTypeEnum::PLAYER)
        {
            if (((pos.x - 0) * (pos.x - 0)) < actorRadiusSquared)
                shape.mShape.setPosition(sf::Vector2f(shape.mShape.getGeometricCenter().x, pos.y));
            else if (((pos.x - mWindow.getSize().x) * (pos.x - mWindow.getSize().x)) < actorRadiusSquared)
                shape.mShape.setPosition(sf::Vector2f(mWindow.getSize().x - shape.mShape.getGeometricCenter().x, pos.y));
            if (((pos.y - 0) * (pos.y - 0)) < actorRadiusSquared)
                shape.mShape.setPosition(sf::Vector2f(pos.x, shape.mShape.getGeometricCenter().y));
            else if (((pos.y - mWindow.getSize().y) * (pos.y - mWindow.getSize().y)) < actorRadiusSquared)
                shape.mShape.setPosition(sf::Vector2f(pos.x, mWindow.getSize().y - shape.mShape.getGeometricCenter().y));
        }
        else
        {
            // If DistSquared < ColliRadiusSquared -> collision;
            if (((pos.x - 0) * (pos.x - 0)) < actorRadiusSquared || ((pos.x - mWindow.getSize().x) * (pos.x - mWindow.getSize().x)) < actorRadiusSquared)
                transform.speed.x *= -1;
            if (((pos.y - 0) * (pos.y - 0)) < actorRadiusSquared || ((pos.y - mWindow.getSize().y) * (pos.y - mWindow.getSize().y)) < actorRadiusSquared)
                transform.speed.y *= -1;
        }        
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
            {
                mMouseCapture = sf::Mouse::getPosition(mWindow);
                player->get<Components::CInput>().mShoot = 1;
            }
            if (buttonPressed->button == sf::Mouse::Button::Right)
            {
                specials = mActorData.specialAmount;
            }
        }
    }

    void GameEngine::sEnemySpawner()
    {
        if (activeEnemies >= MAX_ENEMY_SPAN)
            return;

        if (mFrameCounter % mEnemyData.spanwinterval == 0)
        {
            auto enemy = mActorManager.createActor(Actor::ActorTypeEnum::ENEMY);
            // +-50.0 so enemies don't spawn touching the borders
            float x = Tools::General::random<float>(50.0f, (float)(mWindow.getSize().x) - 50.0f);
            float y = Tools::General::random<float>(50.0f, (float)(mWindow.getSize().y) - 50.0f);

            // COMPONENT.TRANSFORM
            float speedx = Tools::General::random<float>(mEnemyData.speed[0], mEnemyData.speed[1]);
            float speedy = Tools::General::random<float>(mEnemyData.speed[0], mEnemyData.speed[1]);
            enemy->add<Components::CTransform>(Tools::Science::Vec2(x, y),
                Tools::Science::Vec2(speedx, speedy));

            // COMPONENT.SHAPE
            int v = Tools::General::random<int>(mEnemyData.vertices[0], mEnemyData.vertices[1]);
            auto& componentShape = enemy->add<Components::CShape>(mEnemyData.radius, font, v);
            componentShape.mShape.setFillColor(sf::Color::Black);
            sf::Color color(Tools::General::random<int>(0, 200), Tools::General::random<int>(0, 200), Tools::General::random<int>(0, 200));
            componentShape.mShape.setOutlineColor(color);
            componentShape.mShape.setOutlineThickness(mEnemyData.outlinethickness);
            componentShape.mShape.setPosition(sf::Vector2f(x, y));

            // COMPONENT.SHAPE::label
            componentShape.mLabel.setString(sf::String(""));
            //componentShape.mLabel.setCharacterSize(mConfigFile["fonts"][0]["size"].get<int>());
            //componentShape.mLabel.setFillColor(sf::Color(mConfigFile["fonts"][0]["color"][0].get<int>(),
            //    mConfigFile["fonts"][0]["color"][1].get<int>(),
            //    mConfigFile["fonts"][0]["color"][2].get<int>()));
            //componentShape.mLabel.setOrigin(componentShape.mLabel.getLocalBounds().getCenter());
            // MUST set Font here or else the reference is lost for some reason
            componentShape.mLabel.setFont(componentShape.mFont);

            //COMPONENT.COLLISION
            enemy->add<Components::CCollision>(mEnemyData.collisionradius);

            activeEnemies++;
        }
    }
    
    void GameEngine::sSmallEnemySpawner(ActorManager::ActorPtr enemyDestroyed)
    {
        auto enemyShape = enemyDestroyed->get<Components::CShape>().mShape;
        int amount = enemyShape.getPointCount();
        float degrees = 360.0 / amount;
        auto spawnPoint = enemyShape.getPosition();
        sf::Color color = enemyShape.getOutlineColor();
        float radius = mEnemyData.radius / 5;

        for (int i = 0; i < amount; i++)
        {
            auto enemy = mActorManager.createActor(Actor::ActorTypeEnum::ENEMY_MINI);
            Tools::Science::Vec2 speed;
            speed.polar(degrees * i, 1.0);

            // COMPONENT.TRANSFORM
            enemy->add<Components::CTransform>(Tools::Science::Vec2(spawnPoint.x, spawnPoint.y), speed);

            // COMPONENT.SHAPE
            auto& componentShape = enemy->add<Components::CShape>(radius, font, amount);
            componentShape.mShape.setFillColor(color);
            componentShape.mShape.setPosition(spawnPoint);

            // COMPONENT.SHAPE::label
            componentShape.mLabel.setString(sf::String(""));
            // MUST set Font here or else the reference is lost for some reason
            componentShape.mLabel.setFont(componentShape.mFont);

            //COMPONENT.COLLISION
            enemy->add<Components::CCollision>(radius);

            //COMPONENT.LIFESPAN
            enemy->add<Components::CLifespan>(mEnemyData.lifespanminis);
        }

    }

    void GameEngine::sShoot(ActorManager::ActorPtr actor)
    {
        float x = actor->get<Components::CShape>().mShape.getPosition().x;
        float y = actor->get<Components::CShape>().mShape.getPosition().y;

        auto bullet = mActorManager.createActor(Actor::ActorTypeEnum::BULLET);

        Tools::Science::Vec2 speed = { mMouseCapture.x - x, mMouseCapture.y - y };
        speed.normalize();
        bullet->add<Components::CTransform>(Tools::Science::Vec2(x, y),
            Tools::Science::Vec2((mBulletData.speed * speed.x), (mBulletData.speed * speed.y)));

        // COMPONENT.SHAPE

        auto& componentShape = bullet->add<Components::CShape>(mBulletData.radius, font, mBulletData.vertices);
        componentShape.mShape.setFillColor(mBulletData.fillcolor);
        componentShape.mShape.setOutlineColor(mBulletData.fillcolor);
        componentShape.mShape.setPosition(sf::Vector2f(x, y));
        // COMPONENT.SHAPE::label
        componentShape.mLabel.setString(sf::String(""));
        // MUST set Font here or else the reference is lost for some reason
        componentShape.mLabel.setFont(componentShape.mFont);

        //COMPONENT.COLLISION
        bullet->add<Components::CCollision>(mBulletData.collisionradius);

        //COMPONENT.LIFESPAN
        bullet->add<Components::CLifespan>(mBulletData.lifespan);

        actor->get<Components::CInput>().mShoot = 0;

    }

    void GameEngine::sInvincibility(ActorManager::ActorPtr actor)
    {
        auto &actorShape = actor->get<Components::CShape>();
        sf::Color color = actorShape.mShape.getOutlineColor();

        if (invincible == 0)
        {
            invincibleBlink = 0;
            invincibleColor = false;

            sf::Color color = sf::Color::White;
            actorShape.mShape.setOutlineColor(color);
            actorShape.mLabel.setFillColor(color);
        }
        else
        {            
            if(invincibleColor)        
                color.a = 255;
            else
                color.a = 0;

            if (invincibleBlink == 0)
            {
                invincibleBlink = 10;
                invincibleColor = !invincibleColor;
                actorShape.mShape.setOutlineColor(color);
                actorShape.mLabel.setFillColor(color);
            }
            invincibleBlink--;
        }
        invincible--;
    }

    void GameEngine::sSpecial(ActorManager::ActorPtr actor)
    {
        if (cooldown > 0)
        {
            specials = 0;
            return;
        }

        if (wait == 0)
        {
            float x = actor->get<Components::CShape>().mShape.getPosition().x;
            float y = actor->get<Components::CShape>().mShape.getPosition().y;

            auto shield = mActorManager.createActor(Actor::ActorTypeEnum::SHIELD);
            shield->add<Components::CTransform>(Tools::Science::Vec2(x, y),
                Tools::Science::Vec2(mActorData.speed, mActorData.speed));

            float radius = mActorData.radius + mActorData.specialSeparation * (1 + mActorData.specialAmount - specials);
            int thick = 2 * mActorData.outlinethickness * (mActorData.specialAmount - specials);
            auto& componentShape = shield->add<Components::CShape>(radius, font, mActorData.vertices);
            componentShape.mShape.setFillColor(sf::Color(0, 0, 0, 0));
            componentShape.mShape.setOutlineColor(sf::Color(108, 187, 209)); // electric teal
            componentShape.mShape.setOutlineThickness(thick);
            componentShape.mShape.setPosition(sf::Vector2f(x, y));
            // COMPONENT.SHAPE::label
            componentShape.mLabel.setString(sf::String(""));
            // MUST set Font here or else the reference is lost for some reason
            componentShape.mLabel.setFont(componentShape.mFont);

            //COMPONENT.COLLISION
            shield->add<Components::CCollision>(radius);

            //COMPONENT.LIFESPAN
            shield->add<Components::CLifespan>(mActorData.specialLifespan);
            
            specials--;
            wait = mActorData.specialSeparation;
        }
        wait--;

        if (specials == 0)
        {
            cooldown = mActorData.specialCooldown;
            wait = 0;
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
            //Dont call ImGui::Render, only call ImGui::SFML::Render
            ImGui::SFML::Render(window);

            window.display();
        }

        ImGui::SFML::Shutdown();
    }

    
}