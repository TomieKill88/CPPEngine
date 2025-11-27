#pragma once

#include "CShape.hpp"

namespace Component
{
	CShape::CShape(float radius, sf::Color& color, size_t pointCount)
	{
		shape.setPointCount(pointCount);
		shape.setRadius(radius);
		shape.setFillColor(color);
		shape.setOrigin({radius, radius});
		exists = true;
	}

}
