#pragma once

#include <SFML/Graphics.hpp>

#include "Component.hpp"

namespace Component
{
	class CShape : public Component
	{

	public:

		sf::CircleShape shape;

		CShape() = default;
		CShape(float radius, sf::Color& color, size_t pointCount);

		virtual ~CShape() = default;
	};
}
