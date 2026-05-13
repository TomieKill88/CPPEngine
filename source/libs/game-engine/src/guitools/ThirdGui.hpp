#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseGui.hpp"
#include "scenes/GeoWarsMainScene.hpp"

namespace GuiTools
{
	class ThirdGui : public BaseGui
	{
	private:
		Scene::GeoWarsMainScene* mSceneInterface;

		std::string mShapeNames = "";
		std::string mWindowName = "ThirdGUI";
		char nameInput[100] = "";
		// Combo selection data index
		int currentShapeIndex = 0;
		// Options
		bool drawFigure = true;


	public:

		ThirdGui() = delete;
		ThirdGui(Scene::GeoWarsMainScene* sceneInterface);
		virtual ~ThirdGui() = default;

		void update() override;
	};
}
