#include <SFML/Graphics.hpp>

#include "GeoWarsMainScene.hpp"
#include "GameEngine.hpp"
#include "src/general/Random.hpp"

namespace Scene
{
    void GeoWarsMainScene::registerActions()
    {
        registerAction(GameEngine::Input::InputCode::KEYBOARD_W, ActionTypeEnum::UP);
        registerAction(GameEngine::Input::InputCode::KEYBOARD_UP, ActionTypeEnum::UP);
        registerAction(GameEngine::Input::InputCode::KEYBOARD_S, ActionTypeEnum::DOWN);
        registerAction(GameEngine::Input::InputCode::KEYBOARD_DOWN, ActionTypeEnum::DOWN);
        registerAction(GameEngine::Input::InputCode::KEYBOARD_A, ActionTypeEnum::LEFT);
        registerAction(GameEngine::Input::InputCode::KEYBOARD_LEFT, ActionTypeEnum::LEFT);
        registerAction(GameEngine::Input::InputCode::KEYBOARD_D, ActionTypeEnum::RIGHT);
        registerAction(GameEngine::Input::InputCode::KEYBOARD_RIGHT, ActionTypeEnum::RIGHT);
        registerAction(GameEngine::Input::InputCode::MOUSE_RIGHT, ActionTypeEnum::SPECIAL);
        registerAction(GameEngine::Input::InputCode::MOUSE_LEFT, ActionTypeEnum::SHOOT);
    }

    void GeoWarsMainScene::createPlayer()
    {
        mPlayer = mActorManager.createActor(Actor::ActorTypeEnum::PLAYER);
        // COMPONENT.TRANSFORM
        mPlayer->add<Components::CTransform>(Tools::Science::Vec2(mGameEngine->mWindowData.width / 2, mGameEngine->mWindowData.height / 2),
            Tools::Science::Vec2(mGameEngine->mActorData.speed, mGameEngine->mActorData.speed));

        // COMPONENT.SHAPE
        auto& componentShape = mPlayer->add<Components::CShape>(mGameEngine->mActorData.radius, mGameEngine->font, mGameEngine->mActorData.vertices);
        componentShape.mShape.setFillColor(mGameEngine->mActorData.fillcolor);
        componentShape.mShape.setOutlineColor(mGameEngine->mActorData.outlinecolor);
        componentShape.mShape.setOutlineThickness(mGameEngine->mActorData.outlinethickness);
        componentShape.mShape.setPosition(sf::Vector2f(mGameEngine->mWindowData.width / 2, mGameEngine->mWindowData.height / 2));
        // COMPONENT.SHAPE::label
        componentShape.mLabel.setString(sf::String("player"));
        componentShape.mLabel.setCharacterSize(mGameEngine->mAssetsData.fontsize);
        componentShape.mLabel.setFillColor(mGameEngine->mAssetsData.fontcolor);
        componentShape.mLabel.setOrigin(componentShape.mLabel.getLocalBounds().getCenter());
        // MUST set Font here or else the reference is lost for some reason
        componentShape.mLabel.setFont(componentShape.mFont);

        //COMPONENT.COLLISION
        mPlayer->add<Components::CCollision>(mGameEngine->mActorData.collisionradius);

        //COMPONENT.SCORE
        mPlayer->add<Components::CScore>(0);

        //COMPONENT.INPUT
        mPlayer->add<Components::CInput>(0, 0, 0, 0, 0);
    }

    void GeoWarsMainScene::shSmallEnemySpawner(ActorManager::ActorPtr enemyDestroyed)
    {
        auto enemyShape = enemyDestroyed->get<Components::CShape>().mShape;
        int amount = enemyShape.getPointCount();
        float degrees = 360.0 / amount;
        auto spawnPoint = enemyShape.getPosition();
        sf::Color color = enemyShape.getOutlineColor();
        float radius = mGameEngine->mEnemyData.radius / 5;

        for (int i = 0; i < amount; i++)
        {
            auto enemy = mActorManager.createActor(Actor::ActorTypeEnum::ENEMY_MINI);
            Tools::Science::Vec2 speed;
            speed.polar(degrees * i, 1.0);

            // COMPONENT.TRANSFORM
            enemy->add<Components::CTransform>(Tools::Science::Vec2(spawnPoint.x, spawnPoint.y), speed);

            // COMPONENT.SHAPE
            auto& componentShape = enemy->add<Components::CShape>(radius, mGameEngine->font, amount);
            componentShape.mShape.setFillColor(color);
            componentShape.mShape.setPosition(spawnPoint);

            // COMPONENT.SHAPE::label
            componentShape.mLabel.setString(sf::String(""));
            // MUST set Font here or else the reference is lost for some reason
            componentShape.mLabel.setFont(componentShape.mFont);

            //COMPONENT.COLLISION
            enemy->add<Components::CCollision>(radius);

            //COMPONENT.LIFESPAN
            enemy->add<Components::CLifespan>(mGameEngine->mEnemyData.lifespanminis);
        }

    }

    bool GeoWarsMainScene::shCheckCollision(ActorManager::ActorPtr mainActor, ActorManager::ActorPtr secondaryActor)
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

	GeoWarsMainScene::GeoWarsMainScene(GameEngine::GameEngine* gameEngine) : BaseScene(gameEngine)
	{
        registerActions();
        createPlayer();


        mGuiTools = std::make_unique<GuiTools::ThirdGui>(gameEngine, this);
	}


	void GeoWarsMainScene::update() 
	{
        // Gui tool update begin - widgets - end
        mGuiTools->update();
         
        // Update Actors
        mActorManager.update();

        if (mPlayer->get<Components::CInput>().mShoot)
            sShoot(mPlayer); // Only the player shoots at the moment.
        if (msInvincible >= 0)
        {
            sInvincibility(mPlayer);
            msInvincible--;
        }

        if (msSpecials > 0)
            sSpecial(mPlayer);
        if (msSpecialCooldown > 0)
        {
            msSpecialCooldown--;
            int timeToRepeat = msSpecialCooldown / 60;
            mPlayer->get<Components::CShape>().mLabel.setString(sf::String(std::to_string(timeToRepeat).c_str()));
        }
        else
        {
            mPlayer->get<Components::CShape>().mLabel.setString(sf::String(""));
        }            

        sCollision();

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
                int remain = actor->get<Components::CLifespan>().mRemainingFrames -= 1;
                
                sf::Color out = actor->get<Components::CShape>().mShape.getOutlineColor();
                if (actor->getTag() != Actor::ActorTypeEnum::SHIELD)
                {
                    sf::Color color = actor->get<Components::CShape>().mShape.getFillColor();
                    color.a = 255 * ((float)remain / initial);
                    actor->get<Components::CShape>().mShape.setFillColor(color);
                }                    
                out.a = 255.0 * ((float)remain / initial);
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
                shape.setPosition(mPlayer->get<Components::CShape>().mShape.getPosition());
                continue;
            }
            sMovement(actor);
            sWallCollision(actor);
        }

        sEnemySpawner();        

        ++mFrameCounter;
    }

	void GeoWarsMainScene::doAction(Action pAction)
	{
        if (pAction.getState() == ActionStateEnum::START)
        {
            if (pAction.getType() == ActionTypeEnum::UP)
            {
                mPlayer->get<Components::CInput>().mUp = 1;
            }
            else if (pAction.getType() == ActionTypeEnum::DOWN)
            {
                mPlayer->get<Components::CInput>().mDown = 1;
            }
            else if (pAction.getType() == ActionTypeEnum::LEFT)
            {
                mPlayer->get<Components::CInput>().mLeft = 1;
            }
            else if (pAction.getType() == ActionTypeEnum::RIGHT)
            {
                mPlayer->get<Components::CInput>().mRight = 1;
            }
            else if (pAction.getType() == ActionTypeEnum::SHOOT)
            {
                msMouseCapture = sf::Mouse::getPosition(mGameEngine->getWindow());
                mPlayer->get<Components::CInput>().mShoot = 1;
            }
            else if (pAction.getType() == ActionTypeEnum::SPECIAL)
            {
                msSpecials = mGameEngine->mActorData.specialAmount;
            }
        }
        else if (pAction.getState() == ActionStateEnum::END)
        {
            if (pAction.getType() == ActionTypeEnum::UP)
            {
                mPlayer->get<Components::CInput>().mUp = 0;
            }
            else if (pAction.getType() == ActionTypeEnum::DOWN)
            {
                mPlayer->get<Components::CInput>().mDown = 0;
            }
            else if (pAction.getType() == ActionTypeEnum::LEFT)
            {
                mPlayer->get<Components::CInput>().mLeft = 0;
            }
            else if (pAction.getType() == ActionTypeEnum::RIGHT)
            {
                mPlayer->get<Components::CInput>().mRight = 0;
            }

        }
	}
	
    void GeoWarsMainScene::sRender() 
	{
        auto activeActors = mActorManager.getAllActors();
        for each (auto & active in activeActors)
        {
            auto& actor = mActorManager.getActor(active);
            if (actor->isAlive())
            {
                auto& shape = actor->get<Components::CShape>();

                mGameEngine->getWindow().draw(shape.mShape);
                //mGameEngine->getWindow().draw(shape.mLabel);

                //for debugging
                auto& coll = actor->get<Components::CCollision>();
                if (coll.mDraw)
                {
                    coll.mShape.setPosition(shape.mShape.getPosition());
                    mGameEngine->getWindow().draw(coll.mShape);
                }
            }
        }
    }

    void GeoWarsMainScene::sMovement(ActorManager::ActorPtr actor)
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

    void GeoWarsMainScene::sCollision()
    {
        auto enemies = mActorManager.getActorsOfType(Actor::ActorTypeEnum::ENEMY);
        auto minis = mActorManager.getActorsOfType(Actor::ActorTypeEnum::ENEMY_MINI);
        auto bullets = mActorManager.getActorsOfType(Actor::ActorTypeEnum::BULLET);
        auto shields = mActorManager.getActorsOfType(Actor::ActorTypeEnum::SHIELD);

        // ENEMY COLLISIONS
        for each (auto & enemy in enemies)
        {
            if (!enemy->isAlive())
                continue;

            // Check if player should be invincible
            if (msInvincible <= 0)
            {
                if (shCheckCollision(mPlayer, enemy))
                {
                    auto spawnPos = mPlayer->get<Components::CTransform>().position;
                    mPlayer->get<Components::CShape>().mShape.setPosition(sf::Vector2f(spawnPos.x, spawnPos.y));
                    mActorManager.destroyActor(enemy->getId());
                    msInvincible = INVINCIBILITY_FRAMES;
                    msActiveEnemies -= 1;
                    continue;
                }
            }

            for each (auto & bullet in bullets)
            {
                if (!bullet->isAlive())
                    continue;

                if (shCheckCollision(enemy, bullet))
                {
                    shSmallEnemySpawner(enemy);
                    mActorManager.destroyActor(enemy->getId());
                    mActorManager.destroyActor(bullet->getId());
                    msActiveEnemies -= 1;
                    break; // break because enemy was destroyed, no need to check with any other bullet
                }
            }
            
            for each(auto shield in shields)
            {
                if (shCheckCollision(enemy, shield))
                {
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
            if (msInvincible <= 0)
            {
                if (shCheckCollision(mPlayer, mini))
                {
                    auto spawnPos = mPlayer->get<Components::CTransform>().position;
                    mPlayer->get<Components::CShape>().mShape.setPosition(sf::Vector2f(spawnPos.x, spawnPos.y));
                    mActorManager.destroyActor(mini->getId());
                    msInvincible = INVINCIBILITY_FRAMES;
                    continue;
                }
            }

            for each (auto & bullet in bullets)
            {
                if (!bullet->isAlive())
                    continue;

                if (shCheckCollision(mini, bullet))
                {
                    mActorManager.destroyActor(mini->getId());
                    mActorManager.destroyActor(bullet->getId());
                    break; // break because bullet was destroyed, no need to check with any other enemy
                }
            }
        }
        
    }

    void GeoWarsMainScene::sWallCollision(ActorManager::ActorPtr actor)
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
            else if (((pos.x - mGameEngine->getWindow().getSize().x) * (pos.x - mGameEngine->getWindow().getSize().x)) < actorRadiusSquared)
                shape.mShape.setPosition(sf::Vector2f(mGameEngine->getWindow().getSize().x - shape.mShape.getGeometricCenter().x, pos.y));
            if (((pos.y - 0) * (pos.y - 0)) < actorRadiusSquared)
                shape.mShape.setPosition(sf::Vector2f(pos.x, shape.mShape.getGeometricCenter().y));
            else if (((pos.y - mGameEngine->getWindow().getSize().y) * (pos.y - mGameEngine->getWindow().getSize().y)) < actorRadiusSquared)
                shape.mShape.setPosition(sf::Vector2f(pos.x, mGameEngine->getWindow().getSize().y - shape.mShape.getGeometricCenter().y));
        }
        else
        {
            // If DistSquared < ColliRadiusSquared -> collision;
            if (((pos.x - 0) * (pos.x - 0)) < actorRadiusSquared || ((pos.x - mGameEngine->getWindow().getSize().x) * (pos.x - mGameEngine->getWindow().getSize().x)) < actorRadiusSquared)
                transform.speed.x *= -1;
            if (((pos.y - 0) * (pos.y - 0)) < actorRadiusSquared || ((pos.y - mGameEngine->getWindow().getSize().y) * (pos.y - mGameEngine->getWindow().getSize().y)) < actorRadiusSquared)
                transform.speed.y *= -1;
        }
    }

    void GeoWarsMainScene::sEnemySpawner()
    {
        if (msActiveEnemies >= MAX_ENEMY_SPAN)
            return;

        if (mFrameCounter % mGameEngine->mEnemyData.spanwinterval == 0)
        {
            auto enemy = mActorManager.createActor(Actor::ActorTypeEnum::ENEMY);
            // +-50.0 so enemies don't spawn touching the borders
            float x = Tools::General::random<float>(50.0f, (float)(mGameEngine->getWindow().getSize().x) - 50.0f);
            float y = Tools::General::random<float>(50.0f, (float)(mGameEngine->getWindow().getSize().y) - 50.0f);

            // COMPONENT.TRANSFORM
            float speedx = Tools::General::random<float>(mGameEngine->mEnemyData.speed[0], mGameEngine->mEnemyData.speed[1]);
            float speedy = Tools::General::random<float>(mGameEngine->mEnemyData.speed[0], mGameEngine->mEnemyData.speed[1]);
            enemy->add<Components::CTransform>(Tools::Science::Vec2(x, y),
                Tools::Science::Vec2(speedx, speedy));

            // COMPONENT.SHAPE
            int v = Tools::General::random<int>(mGameEngine->mEnemyData.vertices[0], mGameEngine->mEnemyData.vertices[1]);
            auto& componentShape = enemy->add<Components::CShape>(mGameEngine->mEnemyData.radius, mGameEngine->font, v);
            componentShape.mShape.setFillColor(sf::Color::Black);
            sf::Color color(Tools::General::random<int>(0, 200), Tools::General::random<int>(0, 200), Tools::General::random<int>(0, 200));
            componentShape.mShape.setOutlineColor(color);
            componentShape.mShape.setOutlineThickness(mGameEngine->mEnemyData.outlinethickness);
            componentShape.mShape.setPosition(sf::Vector2f(x, y));

            // COMPONENT.SHAPE::label
            componentShape.mLabel.setString(sf::String("enemy"));
            componentShape.mLabel.setCharacterSize(mGameEngine->mAssetsData.fontsize);
            componentShape.mLabel.setFillColor(mGameEngine->mAssetsData.fontcolor);
            componentShape.mLabel.setOrigin(componentShape.mLabel.getLocalBounds().getCenter());
            // MUST set Font here or else the reference is lost for some reason
            componentShape.mLabel.setFont(componentShape.mFont);

            //COMPONENT.COLLISION
            enemy->add<Components::CCollision>(mGameEngine->mEnemyData.collisionradius);

            msActiveEnemies++;
        }
    }
    
    void GeoWarsMainScene::sShoot(ActorManager::ActorPtr actor)
    {
        float x = actor->get<Components::CShape>().mShape.getPosition().x;
        float y = actor->get<Components::CShape>().mShape.getPosition().y;

        auto bullet = mActorManager.createActor(Actor::ActorTypeEnum::BULLET);

        Tools::Science::Vec2 speed = { msMouseCapture.x - x, msMouseCapture.y - y };
        speed.normalize();
        bullet->add<Components::CTransform>(Tools::Science::Vec2(x, y),
            Tools::Science::Vec2((mGameEngine->mBulletData.speed * speed.x), (mGameEngine->mBulletData.speed * speed.y)));

        // COMPONENT.SHAPE

        auto& componentShape = bullet->add<Components::CShape>(mGameEngine->mBulletData.radius, mGameEngine->font, mGameEngine->mBulletData.vertices);
        componentShape.mShape.setFillColor(mGameEngine->mBulletData.fillcolor);
        componentShape.mShape.setOutlineColor(mGameEngine->mBulletData.fillcolor);
        componentShape.mShape.setPosition(sf::Vector2f(x, y));
        // COMPONENT.SHAPE::label
        componentShape.mLabel.setString(sf::String(""));
        // MUST set Font here or else the reference is lost for some reason
        componentShape.mLabel.setFont(componentShape.mFont);

        //COMPONENT.COLLISION
        bullet->add<Components::CCollision>(mGameEngine->mBulletData.collisionradius);

        //COMPONENT.LIFESPAN
        bullet->add<Components::CLifespan>(mGameEngine->mBulletData.lifespan);

        actor->get<Components::CInput>().mShoot = 0;
    }

    void GeoWarsMainScene::sSpecial(ActorManager::ActorPtr actor)
    {
        if (msSpecialCooldown > 0)
        {
            msSpecials = 0;
            return;
        }

        if (msSpecialWait == 0)
        {
            float x = actor->get<Components::CShape>().mShape.getPosition().x;
            float y = actor->get<Components::CShape>().mShape.getPosition().y;

            auto shield = mActorManager.createActor(Actor::ActorTypeEnum::SHIELD);
            shield->add<Components::CTransform>(Tools::Science::Vec2(x, y),
                Tools::Science::Vec2(mGameEngine->mActorData.speed, mGameEngine->mActorData.speed));

            float radius = mGameEngine->mActorData.radius + mGameEngine->mActorData.specialSeparation * (1 + mGameEngine->mActorData.specialAmount - msSpecials);
            int thick = 2 * mGameEngine->mActorData.outlinethickness * (mGameEngine->mActorData.specialAmount - msSpecials);
            auto& componentShape = shield->add<Components::CShape>(radius, mGameEngine->font, mGameEngine->mActorData.vertices);
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
            shield->add<Components::CLifespan>(mGameEngine->mActorData.specialLifespan);

            msSpecials--;
            msSpecialWait = mGameEngine->mActorData.specialSeparation;
        }
        msSpecialWait--;

        if (msSpecials == 0)
        {
            msSpecialCooldown = mGameEngine->mActorData.specialCooldown;
            msSpecialWait = 0;
        }
    }

    void GeoWarsMainScene::sInvincibility(ActorManager::ActorPtr actor)
    {
        auto& actorShape = actor->get<Components::CShape>();
        sf::Color color = actorShape.mShape.getOutlineColor();

        if (msInvincible == 0)
        {
            msInvincibleBlink = 0;
            msInvincibleColor = false;

            sf::Color color = sf::Color::White;
            actorShape.mShape.setOutlineColor(color);
            actorShape.mLabel.setFillColor(color);
        }
        else
        {
            if (msInvincibleColor)
                color.a = 255;
            else
                color.a = 0;

            if (msInvincibleBlink == 0)
            {
                msInvincibleBlink = 10;
                msInvincibleColor = !msInvincibleColor;
                actorShape.mShape.setOutlineColor(color);
                actorShape.mLabel.setFillColor(color);
            }
            msInvincibleBlink--;
        }
        msInvincible--;
    }
}