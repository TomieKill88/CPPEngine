#pragma once

#include<cstdint>

#include "Component.hpp"

namespace Component
{
	class CInput : public Component
	{

	public:

		uint8_t left = 0, right = 0, up = 0, down = 0;

		CInput() = default;
		CInput(uint8_t leftIn, uint8_t rightIn, uint8_t upIn, uint8_t downIn);

		virtual ~CInput() = default;
	};
}
