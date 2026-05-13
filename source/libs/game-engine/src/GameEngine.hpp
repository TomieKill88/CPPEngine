#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "guitools/ThirdGui.hpp"
#include "scenes/BaseScene.hpp"
#include "actorfactory/ActorManager.hpp"
#include "actorfactory/Actor.hpp"

namespace GameEngine
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

	struct sAssetsData
	{
		int fontsize = 0;
		sf::Color fontcolor = sf::Color::White;
	};

	class GameEngine
	{		
		//Privates
		nlohmann::json mConfigFile;		

		// Scenes
		std::map<std::string, std::shared_ptr<Scene::BaseScene>> mScenes;
		std::shared_ptr<Scene::BaseScene> mCurrentScene;		
		
		
		// SFML
		sf::RenderWindow mWindow;
		sf::Clock mClock;
		bool mIsRunning = false;

		void processSfmlInput(const sf::Event& event);

	public:

		//Vector<assests>
		sf::Font font;
		sWindowData mWindowData;
		sActorData mActorData;
		sBulletData mBulletData;
		sEnemyData mEnemyData; 
		sAssetsData mAssetsData;

		GameEngine();
		~GameEngine() = default;

		void init();
		void update();
		void render();
		void run();
		void quit();
		void changeScene(std::string& newScene);
		sf::RenderWindow& getWindow();

		//SYSTEMS
		void sInput(Scene::ActionStateEnum pActionState, Input::InputCode pInputCode);
				
		
	};
}
