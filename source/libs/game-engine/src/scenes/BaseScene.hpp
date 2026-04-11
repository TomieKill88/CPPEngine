#pragma once

#include "actorfactory/ActorManager.hpp"

namespace GameEngine
{
	class GameEngine;
}

namespace Scene
{
	class BaseScene
	{
		GameEngine::GameEngine* mGameEngine;
		ActorManager::ActorManager mActorManager;
		// asset vector
		int mFrameCounter = 0;
		// action map
		bool mPaused = false;

	public:
		BaseScene() = default;
		BaseScene(GameEngine::GameEngine* gameEngine) : mGameEngine(gameEngine){}
		~BaseScene() = default;

		void update();
		//virtual void doAction() = 0;
		void render();

		void simulate(int iterations);
		//void doAction(Action action);
		//void registerAction(Action action);

		void invokeActor(Actor::ActorTypeEnum invokeActor);

	};
}