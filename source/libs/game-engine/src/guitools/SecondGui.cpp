#include <string>

#include "SecondGui.hpp"
#include "GameEngine.hpp"

namespace GuiTools
{
	void SecondGui::updateNames()
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

	void SecondGui::updateNamesByType()
	{ }

	SecondGui::SecondGui(GameEngine::GameEngine* gameEngineInterface) : BaseGui(gameEngineInterface)
	{
		updateNames();
	};

	void SecondGui::update()
	{
		if (shown)
		{
			if (!begin(mWindowName))
			{
				end();
			}
			else
			{
				auto player = BaseGui::mGameEngineInterface->mActorManager.getActorsOfType(Actor::ActorTypeEnum::PLAYER);
				auto enemies = BaseGui::mGameEngineInterface->mActorManager.getActorsOfType(Actor::ActorTypeEnum::ENEMY);
				auto bullets = BaseGui::mGameEngineInterface->mActorManager.getActorsOfType(Actor::ActorTypeEnum::BULLET);

				ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
				if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
				{
					if (ImGui::BeginTabItem("Systems"))
					{
						ImGui::SeparatorText("Enemies");
						if (ImGui::Button("Spawn##enemy")) {
							BaseGui::mGameEngineInterface->sEnemySpawner();
						}

						ImGui::SeparatorText("Special");
						if (ImGui::Button("Special")) {
							//BaseGui::mGameEngineInterface->sEnemySpawner();
						}

						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Entities"))
					{
						if (ImGui::TreeNode("Player"))
						{
							if (player.size() > 0)
							{
								auto obj = player[0];
								auto pos = obj->get<Components::CShape>().mShape.getPosition();
								ImGui::Text("Player");
								ImGui::SameLine();
								if (ImGui::Button("D##Player")) { 
									BaseGui::mGameEngineInterface->mActorManager.destroyActor(obj->getId()); 
								}

								ImGui::SameLine();
								std::string spos = std::to_string(pos.x) + "  " + std::to_string(pos.y);
								ImGui::Text(spos.c_str());

								ImGui::SameLine();
								std::string dest = "C##" + obj->getTagString();
								ImGui::Checkbox("CPlayer", &obj->get<Components::CCollision>().mDraw);

							}

							ImGui::TreePop();
							ImGui::Spacing();					
						}
						if (ImGui::TreeNode("Enemies"))
						{

							for each (auto enemy in enemies)
							{
						
								auto pos = enemy->get<Components::CShape>().mShape.getPosition();
								std::string dest = "D##" + enemy->getTagString();
								ImGui::Text(enemy->getTagString().c_str());
								ImGui::SameLine();
								if (ImGui::Button(dest.c_str())) {
									BaseGui::mGameEngineInterface->mActorManager.destroyActor(enemy->getId());
									BaseGui::mGameEngineInterface->activeEnemies -= 1;
								}

								ImGui::SameLine();
								std::string spos = std::to_string(pos.x) + "  " + std::to_string(pos.y);
								ImGui::Text(spos.c_str());

								ImGui::SameLine();
								std::string scol = "C##" + enemy->getTagString();
								ImGui::Checkbox(scol.c_str(), &enemy->get<Components::CCollision>().mDraw);
							}

							ImGui::TreePop();
							ImGui::Spacing();
						}
						if (ImGui::TreeNode("Bullets"))
				{
					for each (auto bullet in bullets)
					{
						auto pos = bullet->get<Components::CShape>().mShape.getPosition();
						std::string dest = "D##" + bullet->getTagString();
						ImGui::Text(bullet->getTagString().c_str());
						ImGui::SameLine();
						if (ImGui::Button(dest.c_str())) {
							BaseGui::mGameEngineInterface->mActorManager.destroyActor(bullet->getId());
						}

						ImGui::SameLine();
						std::string spos = std::to_string(pos.x) + "  " + std::to_string(pos.y);
						ImGui::Text(spos.c_str());

						ImGui::SameLine();
						std::string scol = "C##" + bullet->getTagString();
						ImGui::Checkbox(scol.c_str(), &bullet->get<Components::CCollision>().mDraw);
					}

					ImGui::TreePop();
					ImGui::Spacing();
				}
						
						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}
				
				end();
			}
		}
	}
}
