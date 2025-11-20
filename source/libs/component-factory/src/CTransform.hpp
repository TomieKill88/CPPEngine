#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "Component.hpp"
#include "src/Vec2.hpp"

namespace Component
{
	class CTransform : public Component
	{

	public:

		Tools::Vec2 position = { 0.0f, 0.0f };
		Tools::Vec2 speed = { 0.0f, 0.0f };

		CTransform() = default;
		CTransform(const Tools::Vec2& pPosition, const Tools::Vec2& pSpeed);

		virtual ~CTransform() = default;
	};
}
