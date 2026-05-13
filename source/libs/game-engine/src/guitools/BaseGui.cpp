#include "BaseGui.hpp"
#include "GameEngine.hpp"

namespace GuiTools
{	

	//BaseGui::BaseGui(GameEngine::GameEngine* gameEngineInterface) : mGameEngineInterface(gameEngineInterface) {};

	bool BaseGui::begin(std::string& title)
	{
		return ImGui::Begin(title.c_str(), &shown);
	}

	void BaseGui::end()
	{
		ImGui::End();
	}

	void BaseGui::show(bool pshow)
	{
		shown = pshow;
	}
}