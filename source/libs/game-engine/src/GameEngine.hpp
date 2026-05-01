#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "guitools/SecondGui.hpp"
#include "scenes/BaseScene.hpp"
#include "actorfactory/ActorManager.hpp"
#include "actorfactory/Actor.hpp"

namespace GameEngine
{
	class GameEngine
	{
		struct sWindowData
		{
			int width = 0;
			int height = 0;
			int framerate = 0;
			bool fullscreen = false;
		};

		struct sActorData
		{
			float radius = 0.0;
			float collisionradius = 0.0;
			int vertices = 0;
			float speed = 0.0;
			sf::Color fillcolor = sf::Color::White;
			sf::Color outlinecolor = sf::Color::White;
			int outlinethickness = 0;
			int specialAmount = 0;
			int specialLifespan = 0;
			int specialSeparation = 0;
			int specialCooldown = 0;
		};

		struct sBulletData
		{
			float radius = 0.0;
			float collisionradius = 0.0;
			int vertices = 0;
			float speed = 0.0;
			sf::Color fillcolor = sf::Color::White;
			int lifespan = 0;
		};

		struct sEnemyData
		{
			float radius = 0.0;
			float collisionradius = 0.0;
			int vertices[2] = { 0, 0 };
			float speed[2] = { 0.0, 0.0 };
			sf::Color outlinecolor = sf::Color::Red;
			int outlinethickness = 0;
			int lifespanminis = 0;
			int spanwinterval = -1;
		};

		//Privates
		sf::Font font;
		sf::Vector2i mMouseCapture;

		int mFrameCounter = 0;
		nlohmann::json mConfigFile;
		sWindowData mWindowData;
		sActorData mActorData;
		sBulletData mBulletData;
		sEnemyData mEnemyData;
		

		// Scenes
		std::map<std::string, Scene::BaseScene> mScenes;
		std::string	mCurrentScene;

		//Vector<assests>
		
		//Actions
		
		//GUIs
		std::unique_ptr<GuiTools::SecondGui> mGuiTools;
		
		// SFML
		sf::RenderWindow mWindow;
		sf::Clock mClock;
		bool mIsRunning = false;

	public:

		// Actors
		ActorManager::ActorManager mActorManager;

		GameEngine();
		~GameEngine() = default;

		void init();
		void update();
		void render();
		void run();
		void quit();
		void changeScene(std::string& newScene);
		const sf::RenderWindow& getWindow();
		


		//SYSTEMS
		void sMovement(ActorManager::ActorPtr actor);
		bool sCollision(ActorManager::ActorPtr mainActor, ActorManager::ActorPtr secondaryActor);
		void sWallCollision(ActorManager::ActorPtr actor);
		void sInput(const sf::Event& event);
		void sEnemySpawner();
		void sSmallEnemySpawner(ActorManager::ActorPtr enemyDestroyed);
		void sShoot(ActorManager::ActorPtr actor);
		void sInvincibility(ActorManager::ActorPtr actor);
		void sSpecial(ActorManager::ActorPtr actor);


		// TEMP -> to move later
		int MAX_ENEMY_SPAN = 10;
		int INVINCIBILITY_FRAMES = 180;
		int activeEnemies = 0;
		int invincible = -1;
		int invincibleBlink = 0;
		bool invincibleColor = false;
		int specials = 0;
		int cooldown = 0;
		int wait = 0;
		
	};


	void callWindowTest();
}
