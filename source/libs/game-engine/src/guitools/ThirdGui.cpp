#include <string>

#include "ThirdGui.hpp"
#include "GameEngine.hpp"

namespace GuiTools
{

	ThirdGui::ThirdGui(Scene::GeoWarsMainScene* sceneInterface) : mSceneInterface(sceneInterface)
	{
	};

	void ThirdGui::update()
	{
		if (shown)
		{
			if (!begin(mWindowName))
			{
				end();
			}
			else
			{
				auto player = mSceneInterface->mActorManager.getActorsOfType(Actor::ActorTypeEnum::PLAYER);
				auto enemies = mSceneInterface->mActorManager.getActorsOfType(Actor::ActorTypeEnum::ENEMY);
				auto bullets = mSceneInterface->mActorManager.getActorsOfType(Actor::ActorTypeEnum::BULLET);

				ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
				if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
				{
					if (ImGui::BeginTabItem("Systems"))
					{
						ImGui::SeparatorText("Enemies");
						if (ImGui::Button("Spawn##enemy")) {
							mSceneInterface->sEnemySpawner();
						}

						ImGui::SeparatorText("Actions");
						ImGui::Text("UP");
						ImGui::SameLine();
						if (ImGui::Button("START##up")) {
							mSceneInterface->sInput(Scene::ActionStateEnum::START, GameEngine::Input::InputCode::KEYBOARD_UP);
						}
						ImGui::SameLine();
						if (ImGui::Button("END##up")) {
							mSceneInterface->sInput(Scene::ActionStateEnum::END, GameEngine::Input::InputCode::KEYBOARD_UP);
						}

						ImGui::Text("DOWN");
						ImGui::SameLine();
						if (ImGui::Button("START##down")) {
							mSceneInterface->sInput(Scene::ActionStateEnum::START, GameEngine::Input::InputCode::KEYBOARD_DOWN);
						}
						ImGui::SameLine();
						if (ImGui::Button("END##down")) {
							mSceneInterface->sInput(Scene::ActionStateEnum::END, GameEngine::Input::InputCode::KEYBOARD_DOWN);
						}

						ImGui::Text("LEFT");
						ImGui::SameLine();
						if (ImGui::Button("START##left")) {
							mSceneInterface->sInput(Scene::ActionStateEnum::START, GameEngine::Input::InputCode::KEYBOARD_LEFT);
						}
						ImGui::SameLine();
						if (ImGui::Button("END##left")) {
							mSceneInterface->sInput(Scene::ActionStateEnum::END, GameEngine::Input::InputCode::KEYBOARD_LEFT);
						}

						ImGui::Text("RIGHT");
						ImGui::SameLine();
						if (ImGui::Button("START##right")) {
							mSceneInterface->sInput(Scene::ActionStateEnum::START, GameEngine::Input::InputCode::KEYBOARD_RIGHT);
						}
						ImGui::SameLine();
						if (ImGui::Button("END##right")) {
							mSceneInterface->sInput(Scene::ActionStateEnum::END, GameEngine::Input::InputCode::KEYBOARD_RIGHT);
						}

						ImGui::Text("SPECIAL");
						ImGui::SameLine();
						if (ImGui::Button("START##special")) {
							mSceneInterface->sInput(Scene::ActionStateEnum::START, GameEngine::Input::InputCode::MOUSE_RIGHT);
						}
						ImGui::SameLine();
						if (ImGui::Button("END##special")) {
							mSceneInterface->sInput(Scene::ActionStateEnum::START, GameEngine::Input::InputCode::MOUSE_RIGHT);
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
