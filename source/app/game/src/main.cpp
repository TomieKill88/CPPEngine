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
#include "src/CTransform.hpp"
#include "src/engine.hpp"
#include "src/FirstGui.hpp"
#include "src/Vec2.hpp"


int main(int argc, char* argv[])
{

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

	auto active = testManager.getAllActors();
	std::cout << "Active actors " <<  active.size() << std::endl;

	auto activeBullet = testManager.getActorsOfType(Actor::ActorTypeEnum::BULLET);
	std::cout << "Active bullets " << activeBullet.size() << std::endl;

	auto activepPlayer= testManager.getActorsOfType(Actor::ActorTypeEnum::PLAYER);
	std::cout << "Active player " << activepPlayer.size() << std::endl;

	std::cout << "Total actors " << testManager.createdActors;

	return 0;
}