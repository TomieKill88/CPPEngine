#pragma once

// https://pthom.github.io/imgui_manual_online/
// https://ruurdsdevlog.wordpress.com/2020/03/07/c-desktop-application-with-dear-imgui/
#include <string>

namespace CustomGui
{
	class BaseGui
	{
	protected:

		bool shown = true;

		bool begin(std::string& title);
		void end();

	public:
		BaseGui() = default;
		virtual ~BaseGui() = default;

		virtual void update() = 0;
		void show(bool pshow);
	};
}