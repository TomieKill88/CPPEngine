#pragma once

#include "Action.hpp"
#include "InputCodes.hpp"
#include "actorfactory/ActorManager.hpp"

namespace GameEngine
{
	class GameEngine;
}

namespace Scene
{
	typedef std::map<GameEngine::Input::InputCode, ActionTypeEnum> ActionMap;

	class BaseScene
	{
	protected:

		GameEngine::GameEngine* mGameEngine;
		ActorManager::ActorManager mActorManager;
		// asset vector
		int mFrameCounter = 0;
		ActionMap mActionMap;
		bool mPaused = false;		

		void simulate(int iterations);

	public:
		BaseScene() = default;
		BaseScene(GameEngine::GameEngine* gameEngine) : mGameEngine(gameEngine){}
		~BaseScene() = default;

		virtual void update() = 0;
		virtual void doAction(Action pAction) = 0;
		virtual void sRender() = 0;
		
		void pause(bool pPause = true);

		void registerAction(GameEngine::Input::InputCode, ActionTypeEnum pActionType);
		bool hasAction(GameEngine::Input::InputCode pActionCode);
		ActionTypeEnum getActionType(GameEngine::Input::InputCode code);

		//void invokeActor(Actor::ActorTypeEnum invokeActor);

	};
}