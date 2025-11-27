#pragma once

#include "Component.hpp"

namespace Component
{
	class CCollision : public Component
	{

	public:

		float radius = 0.0f;

		CCollision() = default;
		CCollision(float pRadius);

		virtual ~CCollision() = default;
	};
}
