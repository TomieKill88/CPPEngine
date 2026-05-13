#pragma once

#include "BaseScene.hpp"

namespace Scene
{
	class GeoWarsMainScene : public BaseScene
	{
	public:
		GeoWarsMainScene() = default;
		GeoWarsMainScene(GameEngine::GameEngine* gameEngine);
		~GeoWarsMainScene() = default;

		void update() override;
		void doAction(Action pAction) override;
		void sRender() override;
	};
}