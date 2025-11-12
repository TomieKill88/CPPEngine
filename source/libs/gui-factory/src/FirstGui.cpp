#include <string>

#include "FirstGui.hpp"

namespace CustomGui
{
	FirstGui::FirstGui(std::vector<std::shared_ptr<CShape::CustomShape>>& shapes) : shapes(shapes) 
	{
		for (auto shape : shapes)
		{
			names += shape->getLabel() + '\0';
		}
	}

	void FirstGui::update()
	{
		if (shown)
		{
			if (!begin(std::string("Shape Controller")))
			{
				end();
			}
			else
			{

				ImGui::SeparatorText("Shape Selector");
				auto label = names.data();
				// Combo box helper allowing to pass all items in a single string literal holding 
				// multiple zero-terminated items "item1\0item2\0"
				ImGui::Combo("shapes", &currentShapeIndex, label);
				currentShapeSelected = shapes[currentShapeIndex];

				end();
			}
		}
	}
}
