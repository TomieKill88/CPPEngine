#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "src/CustomShape.hpp"

class Game
{
public:

	Game() = default;
	~Game() = default;

	void init(std::string& fileName, sf::RenderWindow& window, sf::Font& font, std::vector<std::shared_ptr<CShape::CustomShape>>& shapes);

	int start();
};