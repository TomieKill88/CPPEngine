#pragma once

#include <SFML/Graphics.hpp>

#include "BaseScene.hpp"

namespace Scene
{
	class GeoWarsPauseScene : public BaseScene
	{	
		void registerActions();

	public:
		GeoWarsPauseScene() = default;
		GeoWarsPauseScene(GameEngine::GameEngine* gameEngine);
		~GeoWarsPauseScene() = default;

		void update() override;
		void doAction(Action pAction) override;
		void sRender() override;
	};
}