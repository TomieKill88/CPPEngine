#pragma once

#include "CShape.hpp"

namespace Component
{
	CShape::CShape(float radius, sf::Color color, sf::Color lineColor, int lineThickness, size_t pointCount)
	{
		shape.setPointCount(pointCount);
		shape.setRadius(radius);
		shape.setFillColor(color);
		shape.setOutlineColor(lineColor);
		shape.setOutlineThickness(lineThickness);
		shape.setOrigin({radius, radius});
	}

}
