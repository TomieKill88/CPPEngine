
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "BaseGui.hpp"

namespace CustomGui
{	
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