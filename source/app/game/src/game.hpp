#pragma once


class Game
{
public:

	Game() = default;
	~Game() = default;

	//void init(std::string & fileName, sf::RenderWindow & window, sf::Font & font, std::vector<std::shared_ptr<CShape::CustomShape>>&shapes);

	int start();
};