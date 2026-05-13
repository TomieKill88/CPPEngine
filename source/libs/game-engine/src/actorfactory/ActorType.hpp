#pragma once

#include<cstdint>

#include "src/general/SmartEnum.hpp"

namespace Actor
{
	enum class ActorTypeEnum : uint8_t
	{
		NONE = 0,
		PLAYER,
		SHIELD,
		// ENEMIES
		ENEMY,
		ENEMY_MINI,
		// PROYECTILES
		BULLET,
		// OBJECTS
		TILE
	};

	class ActorType : public Tools::General::SmartEnum<ActorTypeEnum>
	{
	public:

		ActorType();
		ActorType(ActorTypeEnum value);
		virtual ~ActorType() = default;

		std::string toString() override;
	};
}