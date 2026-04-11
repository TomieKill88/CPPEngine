#pragma once

#include <SFML/Graphics.hpp>

#include "guitools/FirstGui.hpp"
#include "scenes/BaseScene.hpp"
#include "actorfactory/Actor.hpp"

namespace GameEngine
{
	class GameEngine
	{
		std::map<std::string, Scene::BaseScene> mScenes;
		std::string	mCurrentScene;

		//Vector<assests>
		//Actions
		//GUIs
		std::unique_ptr<GuiTools::FirstGui> mGuiTools;
		sf::RenderWindow mWindow;
		sf::Clock mClock;
		bool mIsRunning = false;



	public:

		////// TEMP //////
		std::vector<std::shared_ptr<Actor::Actor>> mActorPool;

		GameEngine();
		~GameEngine() = default;

		void init();
		void update();
		void render();
		void run();
		void quit();
		void changeScene(std::string& newScene);
		const sf::RenderWindow& getWindow();
		void userInput();
	};


	void callWindowTest();
}
