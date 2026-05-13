#include <SFML/Graphics.hpp>

#include "GeoWarsMainScene.hpp"

namespace Scene
{
	GeoWarsMainScene::GeoWarsMainScene(GameEngine::GameEngine* gameEngine) : BaseScene(gameEngine)
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


	void GeoWarsMainScene::update() 
	{
        ++mFrameCounter;
    }
	void GeoWarsMainScene::doAction(Action pAction)
	{
        if (pAction.getState() == ActionStateEnum::START)
        {
            if (pAction.getType() == ActionTypeEnum::UP)
            {
                std::cout << "Going up" << std::endl;;
            }
            else if (pAction.getType() == ActionTypeEnum::DOWN)
            {
                std::cout << "Going down" << std::endl;;
            }
            else if (pAction.getType() == ActionTypeEnum::LEFT)
            {
                std::cout << "Going left" << std::endl;;
            }
            else if (pAction.getType() == ActionTypeEnum::RIGHT)
            {
                std::cout << "Going right" << std::endl;;
            }
            else if (pAction.getType() == ActionTypeEnum::SHOOT)
            {
                std::cout << "Shoot" << std::endl;;
            }
            else if (pAction.getType() == ActionTypeEnum::SPECIAL)
            {
                std::cout << "Special" << std::endl;;
            }
        }
        else if (pAction.getState() == ActionStateEnum::END)
        {
            if (pAction.getType() == ActionTypeEnum::UP)
            {
                std::cout << "Stop up" << std::endl;;
            }
            else if (pAction.getType() == ActionTypeEnum::DOWN)
            {
                std::cout << "Stop down" << std::endl;;
            }
            else if (pAction.getType() == ActionTypeEnum::LEFT)
            {
                std::cout << "Stop left" << std::endl;;
            }
            else if (pAction.getType() == ActionTypeEnum::RIGHT)
            {
                std::cout << "Stop right" << std::endl;;
            }

        }
	}
	void GeoWarsMainScene::sRender() 
	{}
}