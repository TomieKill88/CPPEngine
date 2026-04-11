#include "ActorType.hpp"

namespace Actor
{
	ActorType::ActorType() : SmartEnum<ActorTypeEnum>(ActorTypeEnum::NONE)
	{
	}

	ActorType::ActorType(ActorTypeEnum value) : SmartEnum<ActorTypeEnum>(value)
	{
		setEnum(value);
	}


	std::string ActorType::toString()
	{
		std::string name = "";

		switch (mValue) {
		case (ActorTypeEnum::NONE):
			name = std::string("NONE");
			break;
		case (ActorTypeEnum::PLAYER):
			name = std::string("PLAYER");
			break;
		case (ActorTypeEnum::ENEMY):
			name = std::string("ENEMY");
			break;
		case (ActorTypeEnum::BULLET):
			name = std::string("BULLET");
			break;
		case (ActorTypeEnum::TILE):
			name = std::string("TILE");
			break;
		default:
			name = std::string("NotFound");
			break;
		}

		return name;
	
	}
}