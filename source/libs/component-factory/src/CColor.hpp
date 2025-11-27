#pragma once

#include<cstdint>

#include "Component.hpp"

namespace Component
{
	class CColor : public Component
	{

	public:

		uint8_t r = 0, g = 0, b = 0, a = 0;

		CColor() = default;
		CColor(uint8_t rIn, uint8_t gIn, uint8_t bIn, uint8_t aIn);

		virtual ~CColor() = default;
	};
}
