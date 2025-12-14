#include <string>

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "GeoWarsGUI.hpp"

namespace CustomGui
{
	GeoWarsGUI::GeoWarsGUI(Actor::ActorManager& actorManager) : mActorManager(actorManager)
	{		
	}

	void GeoWarsGUI::update()
	{
		if (shown)
		{
			if (!begin(std::string("Geometry Wars")))
			{
				end();
			}
			else
			{
                // Not sure what is this BeginChild for but just in case I'll leave it just in case
                //ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
                ImGui::Text("Settings");
                ImGui::Separator();
                if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
                {
                    if (ImGui::BeginTabItem("Systems"))
                    {
                        ImGui::Checkbox("Movement", &mMovement);
                        ImGui::Checkbox("LifeSpawn", &mLifeSpawn);
                        ImGui::Checkbox("Collision", &mCollision);
                        ImGui::Checkbox("Spawning", &mSpawning);

                        ImGui::SliderInt("Spawn Interval", &mSpawnFrames, 0, 100);

                        if (ImGui::Button("Manual Spawn"))
                            tmp++;
                        if (tmp & 1)
                        {
                            ImGui::SameLine();
                            ImGui::Text("Enemy spawned");
                        }
                        
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Settings"))
                    {
                        ImGui::TextWrapped("Background color");
                        
                        
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
               //ImGui::EndChild(); 

                end();
			}
		}
	}
}
