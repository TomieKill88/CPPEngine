#pragma once

#include "BaseScene.hpp"

namespace Scene
{
	class GeoWarsMainScene : public BaseScene
	{
		//GUIs
		//std::unique_ptr<GuiTools::ThirdGui> mGuiTools;

		// Actors
		ActorManager::ActorManager mActorManager;
		ActorManager::ActorPtr mPlayer;

		void registerActions();
		void createPlayer();

		// SYSTEMS VARS
		int MAX_ENEMY_SPAN = 1;
		int INVINCIBILITY_FRAMES = 180;
		sf::Vector2i msMouseCapture;
		int msSpecials = 0;
		int msSpecialCooldown = 0;
		int msSpecialWait = 0;
		int msInvincible = -1;
		int msInvincibleBlink = 0;
		bool msInvincibleColor = false;
		int msActiveEnemies = 0;
		// SYSTEMS HELPERS
		void shSmallEnemySpawner(ActorManager::ActorPtr enemyDestroyed);
		bool shCheckCollision(ActorManager::ActorPtr mainActor, ActorManager::ActorPtr secondaryActor);

	public:
		GeoWarsMainScene() = default;
		GeoWarsMainScene(GameEngine::GameEngine* gameEngine);
		~GeoWarsMainScene() = default;

		void update() override;
		void doAction(Action pAction) override;
		void sRender() override;

		// SYSTEMS
		void sMovement(ActorManager::ActorPtr actor);
		void sCollision();
		void sWallCollision(ActorManager::ActorPtr actor);
		void sEnemySpawner();
		void sShoot(ActorManager::ActorPtr actor);
		void sSpecial(ActorManager::ActorPtr actor);
		void sInvincibility(ActorManager::ActorPtr actor);
	};
}