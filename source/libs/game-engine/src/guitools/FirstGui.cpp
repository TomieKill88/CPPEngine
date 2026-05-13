#include <string>

#include "FirstGui.hpp"
#include "GameEngine.hpp"

namespace GuiTools
{
	/*
	FirstGui::FirstGui(std::vector<std::shared_ptr<CShape::CustomShape>>& shapes) : shapes(shapes) 
	{		

		for (auto shape : shapes)
		{
			names += shape->getLabel() + '\0';
		}
	}
	*/

	void FirstGui::updateNames()
	{
		mShapeNames = "";

		mActiveActorsIndex = BaseGui::mGameEngineInterface->mActorManager.getAllActors();
		for (auto active : mActiveActorsIndex)
		{
			auto& actor = BaseGui::mGameEngineInterface->mActorManager.getActor(active);
			auto shape = actor->get<Components::CShape>();
			mShapeNames += shape.mLabel.getString() + '\0';
		}
	}

	void FirstGui::updateNamesByType()
	{ }

	FirstGui::FirstGui(GameEngine::GameEngine* gameEngineInterface) : BaseGui(gameEngineInterface) 
	{
		updateNames();
	};

	void FirstGui::update()
	{
		if (shown)
		{
			if (!begin(mWindowName))
			{
				end();
			}
			else
			{
				updateNames();
				ImGui::SeparatorText("Shape Selector");
				ImGui::Combo("shapes", &currentShapeIndex, mShapeNames.c_str());
				auto &currentShapeSelected = BaseGui::mGameEngineInterface->mActorManager.getActor(mActiveActorsIndex[currentShapeIndex]);
				auto &selectedShape = currentShapeSelected->get<Components::CShape>();

				ImGui::SameLine(); if (ImGui::Button("D"))
				{
					BaseGui::mGameEngineInterface->mActorManager.destroyActor(mActiveActorsIndex[currentShapeIndex]);
				}

				//////////  Shape name  ///////////////

				ImGui::InputTextWithHint("Name", "Enter shape name", nameInput, IM_ARRAYSIZE(nameInput));
				ImGui::SameLine(); if (ImGui::Button("Set"))
				{
					selectedShape.mLabel.setString(sf::String(nameInput));
					selectedShape.mLabel.setOrigin(selectedShape.mLabel.getLocalBounds().getCenter());
				}

				//////////  Shape size  ///////////////

				float radius = selectedShape.mShape.getRadius();
				ImGui::SliderFloat("Radius", &radius, 1.0f, 200.0f, "%.1f", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp);
				selectedShape.mShape.setRadius(radius);
				
				//////////  Shape Color  ///////////////
				sf::Color shapeColor;
				// Set width of next widget (popItemWidth to revert)
				ImGui::PushItemWidth(30);
				// Put 0 in step so there are no buttons
				ImGui::InputInt("R", &color[0], 0);
				if (color[0] < 0) color[0] = 0;
				if (color[0] > 255) color[0] = 255;
				shapeColor.r = static_cast<uint8_t>(color[0]);

				ImGui::SameLine();
				// Set width of next widget (popItemWidth to revert)
				ImGui::PushItemWidth(30);
				// Put 0 in step so there are no buttons
				ImGui::InputInt("G", &color[1], 0);
				if (color[1] < 0) color[1] = 0;
				if (color[1] > 255) color[1] = 255;
				shapeColor.g = static_cast<uint8_t>(color[1]);

				ImGui::SameLine();
				// Set width of next widget (popItemWidth to revert)
				ImGui::PushItemWidth(30);
				// Put 0 in step so there are no buttons
				ImGui::InputInt("B", &color[2], 0);
				if (color[2] < 0) color[2] = 0;
				if (color[2] > 255) color[2] = 255;
				shapeColor.b = static_cast<uint8_t>(color[2]);

				ImGui::SameLine(); if (ImGui::Button("Set##Color")) { selectedShape.mShape.setFillColor(shapeColor); }

				/*
				ImGui::SeparatorText("Shape Selector");
				auto label = mShapeNames.data();
				// Combo box helper allowing to pass all items in a single string literal holding 
				// multiple zero-terminated items "item1\0item2\0"
				ImGui::Combo("shapes", &currentShapeIndex, label);
				//currentShapeSelected = shapes[currentShapeIndex];

				ImGui::SeparatorText("Options");
				//drawFigure = currentShapeSelected->isEnabled();
				ImGui::Checkbox("Draw Figure", &drawFigure);
				//currentShapeSelected->enable(drawFigure);

				//scale = currentShapeSelected->getScale();
				ImGui::SliderFloat("Scale", &scale, 0.0f, 5.0f, "%.2f");
				//currentShapeSelected->setScale(scale);								
				
				//sf::Vector2f tmpv = currentShapeSelected->getVelocity();
				//vel[0] = tmpv.x; vel[1] = tmpv.y;
				ImGui::InputFloat2("Velocity", vel, "%.1f");
				//currentShapeSelected->setVelocity({vel[0], vel[1]});

				//sf::Color tmpc = currentShapeSelected->getColor();
				//color[0] = tmpc.r; color[1] = tmpc.g; color[2] = tmpc.b;
				ImGui::InputInt3("Color", color);
				//currentShapeSelected->setColor(color[0], color[1], color[2]);

				//if (ImGui::Button("Reset"))
				//	currentShapeSelected->reset();
				*/
				end();
			}
		}
	}
}
