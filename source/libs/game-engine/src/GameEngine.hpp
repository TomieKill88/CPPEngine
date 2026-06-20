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
		float speed = 0.0;
		std::string sprite = "";
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

	struct sFontsData
	{
		sf::Font font;
		int fontsize = 0;
		sf::Color fontcolor = sf::Color::White;
	};

	struct sSpritesData
	{
		sf::Texture* texture;
		sf::IntRect subrect{ {0,0},{0,0} };
	};

	struct sTexturesData
	{
		sf::Texture texture;
		Tools::Science::Vec2 size{ 0.0f, 0.0f };
	};

	class GameEngine
	{		
		friend class GuiTools::ThirdGui;
		//GUIs
		std::unique_ptr<GuiTools::ThirdGui> mGuiTools;

		//Privates
		nlohmann::json mConfigFile;

		// Assets CLASS
		std::map<std::string, sFontsData> mFonts;
		std::map<std::string, sTexturesData> mTextures;
		std::map<std::string, sSpritesData> mSprites;


		// Scenes
		std::map<std::string, std::shared_ptr<Scene::BaseScene>> mScenes;
		std::shared_ptr<Scene::BaseScene> mCurrentScene;
		std::string mCurrenSceneKey = "";
		
		
		// SFML
		sf::RenderWindow mWindow;
		sf::Clock mClock;
		bool mIsRunning = false;

		void processSfmlInput(const sf::Event& event);

	public:

		//Vector<assests>
		sWindowData mWindowData;
		sActorData mActorData;
		sBulletData mBulletData;
		sEnemyData mEnemyData; 
		sFontsData mFontsData;

		GameEngine();
		~GameEngine() = default;

		void init();
		void update();
		void render();
		void run();
		void quit();
		void changeScene(std::string& newScene);
		void saveScene();
		sf::RenderWindow& getWindow();

		//SYSTEMS
		void sInput(Scene::ActionStateEnum pActionState, Input::InputCode pInputCode);

		const sSpritesData& getSpriteData(std::string& sprite);
	};
}
