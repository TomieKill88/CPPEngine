#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseGui.hpp"

namespace Scene
{
	class GeoWarsMainScene;
}

namespace GuiTools
{
	class ThirdGui : public BaseGui
	{
	private:

		Scene::GeoWarsMainScene* mMainSceneInterface;
		std::string mShapeNames = "";
		std::string mWindowName = "ThirdGUI";
		char nameInput[100] = "";
		// Combo selection data index
		int currentShapeIndex = 0;
		// Options
		bool drawFigure = true;


	public:

		ThirdGui() = delete;
		ThirdGui(GameEngine::GameEngine* gameEngineInterface, Scene::GeoWarsMainScene* mainSceneInterface);
		virtual ~ThirdGui() = default;

		void update() override;
	};
}
