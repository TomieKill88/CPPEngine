#pragma once
#include <SFML/Graphics.hpp>

namespace GameEngine
{
	namespace Input
	{
		enum class InputCode
		{
			NONE = -1,
			// Keyboard
			KEYBOARD_A = 0,
			KEYBOARD_D,
			KEYBOARD_S,
			KEYBOARD_W,
			KEYBOARD_UP,
			KEYBOARD_DOWN,
			KEYBOARD_LEFT,
			KEYBOARD_RIGHT,
			KEYBOARD_SPACE,
			KEYBOARD_ESC,
			KEYBOARD_ENTER,
			KEYBOARD_TAB,
			//Mouse
			MOUSE_LEFT,
			MOUSE_RIGHT,
			MOUSE_MIDDLE

		};


		sf::Keyboard::Scancode getSfKeyboardScancode(InputCode pInputCode);

		sf::Mouse::Button getSfMouseButton(InputCode pInputCode);

		InputCode getInputKeyboard(sf::Keyboard::Scancode pKeyboardCode);

		InputCode getInputMouse(sf::Mouse::Button pMouseButton);
	}
}