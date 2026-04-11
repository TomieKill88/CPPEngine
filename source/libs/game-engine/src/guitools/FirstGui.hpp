#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseGui.hpp"
//#include "src/CustomShape.hpp"

namespace GuiTools
{
	class FirstGui : public BaseGui
	{
	private:
		//std::vector<std::shared_ptr<CShape::CustomShape>> shapes;
		//std::shared_ptr<CShape::CustomShape> currentShapeSelected;

		std::string mShapeNames = "";
		std::string mWindowName = "FirstGUI";
		char nameInput[100] = "";
		// Combo selection data index
		int currentShapeIndex = 0;
		// Options
		bool drawFigure = true;
		float scale = 1.0f;
		float vel[2];
		int color[3];

	public:

		FirstGui() = delete;
		FirstGui(GameEngine::GameEngine* gameEngineInterface);
		virtual ~FirstGui() = default;

		void update() override;
	};
}
