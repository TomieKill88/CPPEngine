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
	Game game;

    std::string fileName = "config/config.txt";

    try
    {
        game.init(fileName);
    }
    catch (std::exception& ex)
    {
        std::cout << "Error by initialization: " << ex.what();
        return -1;
    }

	game.start();

	return 0;
}