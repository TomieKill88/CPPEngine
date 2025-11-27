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

		Tools::Vec2<float> position = { 0.0f, 0.0f };
		Tools::Vec2<float> speed = { 0.0f, 0.0f };
		Tools::Vec2<float> scale = { 1.0f, 1.0f };
		float angle = 0.0f;

		CTransform() = default;
		CTransform(const Tools::Vec2<float>& pPosition, const Tools::Vec2<float>& pSpeed, const Tools::Vec2<float>& pScale, float pAngle);

		virtual ~CTransform() = default;
	};
}
