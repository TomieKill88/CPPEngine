#include "BaseScene.hpp"
#include "GameEngine.hpp"


namespace Scene
{
	//BaseScene::BaseScene(GameEngine::GameEngine* gameEngine) : mGameEngine(gameEngine) 
	//{
	//}

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

	void BaseScene::simulate(int iterations)
	{
		for (int i = 0; i < iterations; i++)
		{
			update();
		}
	}

	void BaseScene::pause(bool pPause)
	{
		mPaused = pPause;
	}
}