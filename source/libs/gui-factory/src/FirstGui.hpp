#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseGui.hpp"
#include "src/CustomShape.hpp"

namespace CustomGui 
{
	class FirstGui : public BaseGui
	{
	private:
		std::vector<std::shared_ptr<CShape::CustomShape>> shapes;
		std::shared_ptr<CShape::CustomShape> currentShapeSelected;

		std::string names = "";
		// Combo selection data index
		int currentShapeIndex = 0;

	public:

		FirstGui(std::vector<std::shared_ptr<CShape::CustomShape>>& shapes);
		virtual ~FirstGui() = default;

		void update() override;
	};
}
