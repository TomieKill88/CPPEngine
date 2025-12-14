#include <string>

#include <imgui-SFML.h>
#include <imgui.h>

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

				ImGui::SeparatorText("Options");
				drawFigure = currentShapeSelected->isEnabled();
				ImGui::Checkbox("Draw Figure", &drawFigure);
				currentShapeSelected->enable(drawFigure);

				scale = currentShapeSelected->getScale();
				ImGui::SliderFloat("Scale", &scale, 0.0f, 5.0f, "%.2f");
				currentShapeSelected->setScale(scale);								
				
				sf::Vector2f tmpv = currentShapeSelected->getVelocity();
				vel[0] = tmpv.x; vel[1] = tmpv.y;
				ImGui::InputFloat2("Velocity", vel, "%.1f");
				currentShapeSelected->setVelocity({vel[0], vel[1]});

				sf::Color tmpc = currentShapeSelected->getColor();
				color[0] = tmpc.r; color[1] = tmpc.g; color[2] = tmpc.b;
				ImGui::InputInt3("Color", color);
				currentShapeSelected->setColor(color[0], color[1], color[2]);

				if (ImGui::Button("Reset"))
					currentShapeSelected->reset();

				end();
			}
		}
	}
}
