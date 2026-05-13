#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseGui.hpp"

namespace GuiTools
{
	class SecondGui : public BaseGui
	{
	private:

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

		std::vector<size_t> mActiveActorsIndex;

		void updateNames();
		void updateNamesByType();

	public:

		SecondGui() = delete;
		SecondGui(GameEngine::GameEngine* gameEngineInterface);
		virtual ~SecondGui() = default;

		void update() override;
	};
}
