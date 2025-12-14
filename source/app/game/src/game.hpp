#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "src/ActorManager.hpp"
#include "src/CustomShape.hpp"
#include "src/Actor.hpp"

class Game
{
	struct PlayerData {
		int radius = 0;
		int collisionRadius = 0;
		float speed = 0.0f;
		sf::Color fillColor;
		sf::Color outlineColor;
		int lineThickness = 0;
		int vertices = 3;
	};

	struct EnemyData {
		int radius = 0;
		int collisionRadius = 0;
		float minSpeed = 0.0f;
		float maxSpeed = 0.0f;
		sf::Color outlineColor;
		int lineThickness = 0;
		int maxVertices = 3;
		int lifeSpan = 0;
		int spawnInterval = 0;
	};

	struct BulletData {
		int radius = 0;
		int collisionRadius = 0;
		float speed = 0.0f;
		sf::Color fillColor;
		int vertices = 3;
		int lifeSpan = 0;
	};

private:
	
	sf::RenderWindow window;

	// Assets
	sf::Font font;

	PlayerData playerData;
	EnemyData enemyData;
	BulletData bulletData;

	Actor::ActorManager actorManager;
	Actor::ActorPtr player = nullptr;

	void readConfiguration(std::string& fileName);
	void spawnPlayer();
	void spawnEnemy();
	void spawnBullet();

	// SYSTEM
	void sUserInput();
	void sRender();
	void sMovement();
	void sPhysics();

public:

	Game() = default;
	~Game() = default;	

	void init(std::string& fileName);

	int start();

	sf::RenderWindow& getWindow();

	Actor::ActorManager& getActorManager();

	//int start_OLD();
};