#include <cstdlib> 
#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>

#include "Game.hpp"
#include "src/Actor.hpp"
#include "src/ActorType.hpp"
#include "src/ActorManager.hpp"
#include "src/ConfigFileReader.hpp"
#include "src/CustomShape.hpp"
#include "src/engine.hpp"
#include "src/FirstGui.hpp"
#include "src/Vec2.hpp"
#include "src/BasicTools.hpp"

#include "src/CTransform.hpp"
#include "src/CInput.hpp"
#include "src/CLifeSpawn.hpp"
#include "src/CScore.hpp"
#include "src/CCollision.hpp"
#include "src/CColor.hpp"
#include "src/CShape.hpp"


int main(int argc, char* argv[])
{
	Tools::seed();

	std::cout << Tools::getRandomFloat(6.0, 20.0f) << std::endl;
	std::cout << Tools::getRandomFloat(6.0, 20.0f) << std::endl;
	std::cout << Tools::getRandomFloat(6.0, 20.0f) << std::endl;
	std::cout << Tools::getRandomFloat(6.0, 20.0f) << std::endl;
	std::cout << Tools::getRandomFloat(6.0, 20.0f) << std::endl;
	std::cout << Tools::getRandomFloat(6.0, 20.0f) << std::endl;

	std::cout << Tools::getRandomInt(2, 7) << std::endl;
	std::cout << Tools::getRandomInt(2, 7) << std::endl;
	std::cout << Tools::getRandomInt(2, 7) << std::endl;
	std::cout << Tools::getRandomInt(2, 7) << std::endl;
	std::cout << Tools::getRandomInt(2, 7) << std::endl;
	std::cout << Tools::getRandomInt(2, 7) << std::endl;


	Tools::Vec2f test(sf::Vector2f(4.5, 6.7));

	Tools::Vec2f normal = test.normalized();

	std::cout << "len1 " << test.len() << std::endl;
	std::cout << "len2 " << normal.len() << std::endl;

	Tools::Vec2f test2;
	test2 = sf::Vector2f(5.6, 7.8);

	std::cout << normal.toString() << std::endl;

	Tools::Vec2f test3 = test2 - normal;
	std::cout << test3.toString() << std::endl;

	Actor::ActorManager testManager;

	testManager.createActor(Actor::ActorTypeEnum::BULLET);
	testManager.createActor(Actor::ActorTypeEnum::BULLET);
	testManager.createActor(Actor::ActorTypeEnum::BULLET);
	testManager.createActor(Actor::ActorTypeEnum::BULLET);
	testManager.createActor(Actor::ActorTypeEnum::BULLET);
	testManager.createActor(Actor::ActorTypeEnum::BULLET);

	testManager.createActor(Actor::ActorTypeEnum::ENEMY);
	testManager.createActor(Actor::ActorTypeEnum::ENEMY);
	testManager.createActor(Actor::ActorTypeEnum::ENEMY);
	testManager.createActor(Actor::ActorTypeEnum::ENEMY);

	testManager.createActor(Actor::ActorTypeEnum::PLAYER);

	testManager.update();

	auto activeBullet = testManager.getActorsOfType(Actor::ActorTypeEnum::BULLET);
	auto activepPlayer= testManager.getActorsOfType(Actor::ActorTypeEnum::PLAYER);

	auto trans = activeBullet[0]->add<Component::CTransform>();
	trans.position = Tools::Vec2f(8.9, 5.8);
	trans.angle = 4.6;
	auto life = activeBullet[0]->add<Component::CLifeSpawn>(10);

	auto playtrans = activepPlayer[0]->add<Component::CTransform>(Tools::Vec2f(4.9, 6.8), Tools::Vec2f(1.9, 2.8), Tools::Vec2f(4.0, 6.1), 11);

	std::cout << "active bull trans " << activeBullet[0]->get<Component::CTransform>().position.x << "," << activeBullet[0]->get<Component::CTransform>().position.y << std::endl;
	std::cout << "active bull life " << activeBullet[0]->get<Component::CLifeSpawn>().life << "," << activeBullet[0]->get<Component::CLifeSpawn>().remaining << std::endl;

	std::cout << "active player trans speed " << activepPlayer[0]->get<Component::CTransform>().speed.x << "," << activepPlayer[0]->get<Component::CTransform>().speed.y << std::endl;
	std::cout << "active player angle " << activepPlayer[0]->get<Component::CTransform>().angle << std::endl;

	std::cout << "remove" << std::endl;
	activepPlayer[0]->remove<Component::CTransform>();
	std::cout << "active player trans speed " << activepPlayer[0]->get<Component::CTransform>().speed.x << "," << activepPlayer[0]->get<Component::CTransform>().speed.y << std::endl;



	return 0;
}