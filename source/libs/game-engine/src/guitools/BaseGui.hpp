#pragma once

// https://pthom.github.io/imgui_manual_online/
// https://pthom.github.io/imgui_explorer/
// https://ruurdsdevlog.wordpress.com/2020/03/07/c-desktop-application-with-dear-imgui/
#include <string>

// All apps using this Base GUI will need these libraries
// So I add them here to not add them multiple times
#include <imgui-SFML.h>
#include <imgui.h>

namespace GameEngine
{
	class GameEngine;
};

namespace GuiTools
{
	class BaseGui
	{
	protected:

		//GameEngine::GameEngine *mGameEngineInterface;

		bool shown = true;

		bool begin(std::string& title);
		void end();

	public:

		BaseGui() = delete;
		//BaseGui(GameEngine::GameEngine* gameEngineInterface);
		virtual ~BaseGui() = default;

		virtual void update() = 0;
		void show(bool pshow);
	};
}