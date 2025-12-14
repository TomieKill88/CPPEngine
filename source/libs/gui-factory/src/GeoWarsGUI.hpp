#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "src/ActorManager.hpp"
#include "BaseGui.hpp"


namespace CustomGui 
{
	class GeoWarsGUI : public BaseGui
	{
	private:
		
		Actor::ActorManager mActorManager;

		bool mMovement = true;
		bool mLifeSpawn = true;
		bool mCollision = true;
		bool mSpawning = true;
		int mSpawnFrames = 60;



		int tmp = 0;


	public:

		GeoWarsGUI(Actor::ActorManager& actorManager);
		virtual ~GeoWarsGUI() = default;

		void update() override;
	};
}
