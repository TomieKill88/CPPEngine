#include <fstream>

#include "BaseScene.hpp"
#include "GameEngine.hpp"


namespace Scene
{
	//BaseScene::BaseScene(GameEngine::GameEngine* gameEngine) : mGameEngine(gameEngine) 
	//{
	//}
	void BaseScene::saveScene(std::string& sceneName)
	{
		std::cout << "Saving Game... Don't turn off power..." << std::endl;
		/*{
			"environment": {
			},
			"actors": {
			"player": {
				"position": [ 300, 300 ]
			},
			"enemies": {
				"type": [
				"NORMAL",
				"NORMAL",
				"NORMAL",
				"NORMAL",
				"NORMAL"
				],
				"position": [
				[ 50, 50 ],
				[ 300, 50 ],
				[ 500, 50 ],
				[ 220, 600 ],
				[ 430, 600 ]
				]
			}
			}
		}*/

		auto players = mActorManager.getActorsOfType(Actor::ActorTypeEnum::PLAYER);
		auto tiles = mActorManager.getActorsOfType(Actor::ActorTypeEnum::TILE);
		auto enemies = mActorManager.getActorsOfType(Actor::ActorTypeEnum::ENEMY);

		nlohmann::json j;
		std::vector<std::vector<float>> positions;
		std::vector<std::string> types;

		for each (auto tile in tiles)
		{
			std::vector<float> position;
			position.push_back(tile->get<Components::CTransform>().position.x);
			position.push_back(tile->get<Components::CTransform>().position.y);
			positions.push_back(position);

			types.push_back(Actor::ActorType(tile->getTag()).toString());
		}

		j["environment"]["type"] = types;
		j["environment"]["position"] = positions;

		for each (auto player in players)
		{
			std::vector<float> position;
			position.push_back(player->get<Components::CTransform>().position.x);
			position.push_back(player->get<Components::CTransform>().position.y);
			positions.push_back(position);
		}
		j["actors"]["player"]["position"] = positions;

		positions.clear();
		types.clear();
		for each (auto enemy in enemies)
		{
			std::vector<float> position;
			position.push_back(enemy->get<Components::CTransform>().position.x);
			position.push_back(enemy->get<Components::CTransform>().position.y);
			positions.push_back(position);

			types.push_back(Actor::ActorType(enemy->getTag()).toString());
		}
		j["actors"]["enemies"]["type"] = types;
		j["actors"]["enemies"]["position"] = positions;

		try
		{
			std::string name = "config/" + sceneName + "config.json";
			std::ofstream config(name);

			config << j.dump(1) << std::endl; //Dump(space) prints in formated json instead of a single line
		}
		catch(std::exception& ex)
		{
			std::cout << "ERROR: scene couldn't be saved: " << ex.what() << std::endl;
		}
		
		std::cout << "Game saved successfully!" << std::endl;
	}

	void BaseScene::simulate(int iterations)
	{
		for (int i = 0; i < iterations; i++)
		{
			update();
		}
	}

	void BaseScene::registerAction(GameEngine::Input::InputCode pActionCode, ActionTypeEnum pActionType)
	{
		mActionMap[pActionCode] = pActionType;
	}

	bool BaseScene::hasAction(GameEngine::Input::InputCode action)
	{
		return (mActionMap.find(action) != mActionMap.end());
	}

	ActionTypeEnum BaseScene::getActionType(GameEngine::Input::InputCode code)
	{
		return mActionMap[code];
	}


	void BaseScene::pause(bool pPause)
	{
		mPaused = pPause;
	}
}