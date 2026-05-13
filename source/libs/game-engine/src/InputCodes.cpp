#include <iostream>

#include "InputCodes.hpp"

namespace GameEngine
{
	namespace Input
	{
		sf::Keyboard::Scancode getSfKeyboardScancode(InputCode pInputCode)
		{
			if (pInputCode == InputCode::KEYBOARD_A)
				return sf::Keyboard::Scancode::A;
			else if (pInputCode == InputCode::KEYBOARD_D)
				return sf::Keyboard::Scancode::D;
			else if (pInputCode == InputCode::KEYBOARD_S)
				return sf::Keyboard::Scancode::S;
			else if (pInputCode == InputCode::KEYBOARD_W)
				return sf::Keyboard::Scancode::W;
			else if (pInputCode == InputCode::KEYBOARD_UP)
				return sf::Keyboard::Scancode::Up;
			else if (pInputCode == InputCode::KEYBOARD_DOWN)
				return sf::Keyboard::Scancode::Down;
			else if (pInputCode == InputCode::KEYBOARD_LEFT)
				return sf::Keyboard::Scancode::Left;
			else if (pInputCode == InputCode::KEYBOARD_RIGHT)
				return sf::Keyboard::Scancode::Right;
			else if (pInputCode == InputCode::KEYBOARD_SPACE)
				return sf::Keyboard::Scancode::Space;
			else if (pInputCode == InputCode::KEYBOARD_ESC)
				return sf::Keyboard::Scancode::Escape;
			else if (pInputCode == InputCode::KEYBOARD_ENTER)
				return sf::Keyboard::Scancode::Enter;
			else if (pInputCode == InputCode::KEYBOARD_TAB)
				return sf::Keyboard::Scancode::Tab;
			else
			{
				std::cout << "ERROR: Keyboard Code not defined" << std::endl;
				return sf::Keyboard::Scancode::Unknown;
			}
		}

		sf::Mouse::Button getSfMouseButton(InputCode pInputCode)
		{
			if (pInputCode == InputCode::MOUSE_LEFT)
				return sf::Mouse::Button::Left;
			else if (pInputCode == InputCode::MOUSE_MIDDLE)
				return sf::Mouse::Button::Middle;
			else if (pInputCode == InputCode::MOUSE_RIGHT)
				return sf::Mouse::Button::Right;
			else
			{
				std::cout << "ERROR: Keyboard Code not defined" << std::endl;
				return sf::Mouse::Button::Extra2;
			}
		}

		InputCode getInputKeyboard(sf::Keyboard::Scancode pKeyboardCode)
		{
			if (pKeyboardCode == sf::Keyboard::Scancode::A)
				return InputCode::KEYBOARD_A;
			else if (pKeyboardCode == sf::Keyboard::Scancode::D)
				return InputCode::KEYBOARD_D;
			else if (pKeyboardCode == sf::Keyboard::Scancode::S)
				return InputCode::KEYBOARD_S;
			else if (pKeyboardCode == sf::Keyboard::Scancode::W)
				return InputCode::KEYBOARD_W;
			else if (pKeyboardCode == sf::Keyboard::Scancode::Up)
				return InputCode::KEYBOARD_UP;
			else if (pKeyboardCode == sf::Keyboard::Scancode::Down)
				return InputCode::KEYBOARD_DOWN;
			else if (pKeyboardCode == sf::Keyboard::Scancode::Left)
				return InputCode::KEYBOARD_LEFT;
			else if (pKeyboardCode == sf::Keyboard::Scancode::Right)
				return InputCode::KEYBOARD_RIGHT;
			else if (pKeyboardCode == sf::Keyboard::Scancode::Space)
				return InputCode::KEYBOARD_SPACE;
			else if (pKeyboardCode == sf::Keyboard::Scancode::Escape)
				return InputCode::KEYBOARD_ESC;
			else if (pKeyboardCode == sf::Keyboard::Scancode::Enter)
				return InputCode::KEYBOARD_ENTER;
			else if (pKeyboardCode == sf::Keyboard::Scancode::Tab)
				return InputCode::KEYBOARD_TAB;
			else
			{
				std::cout << "ERROR: Keyboard Code not defined" << std::endl;
				return InputCode::NONE;
			}
		}

		InputCode getInputMouse(sf::Mouse::Button pMouseButton)
		{
			if (pMouseButton == sf::Mouse::Button::Left)
				return InputCode::MOUSE_LEFT;
			else if (pMouseButton == sf::Mouse::Button::Middle)
				return InputCode::MOUSE_MIDDLE;
			else if (pMouseButton == sf::Mouse::Button::Right)
				return InputCode::MOUSE_RIGHT;
			else
			{
				std::cout << "ERROR: Keyboard Code not defined" << std::endl;
				return InputCode::NONE;
			}
		}
	}
}