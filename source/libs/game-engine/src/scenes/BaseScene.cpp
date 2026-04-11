#include "BaseScene.hpp"
#include "GameEngine.hpp"


namespace Scene
{
	//BaseScene::BaseScene(GameEngine::GameEngine* gameEngine) : mGameEngine(gameEngine) 
	//{
	//}

	void BaseScene::update()
	{
		mFrameCounter++;
		std::cout << "mFrameCounter: " << mFrameCounter << std::endl;
	}

	void BaseScene::render()
	{
		std::cout << "Rendering" << std::endl;
	}

	void BaseScene::simulate(int iterations)
	{
		for (int i = 0; i < iterations; i++)
		{
			update();
		}
	}
}