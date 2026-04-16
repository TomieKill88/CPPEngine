#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "guitools/FirstGui.hpp"
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

		int mFrameCounter = 0;
		nlohmann::json mConfigFile;
		sWindowData mWindowData;
		sBulletData mBulletData;
		sEnemyData mEnemyData;
		

		// Scenes
		std::map<std::string, Scene::BaseScene> mScenes;
		std::string	mCurrentScene;

		//Vector<assests>
		
		//Actions
		
		//GUIs
		std::unique_ptr<GuiTools::FirstGui> mGuiTools;
		
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


		// TEMP -> to move later
		template<typename T>
		T random(T min, T max)
		{
			static bool first = true;
			if (first)
			{
				srand(time(NULL)); //seeding for the first time only!
				first = false;
			}
			return min + rand() % (int)((max + 1) - min);
		}
	};


	void callWindowTest();
}
