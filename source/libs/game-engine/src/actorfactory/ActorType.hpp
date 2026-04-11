#pragma once

#include<cstdint>

#include "src/SmartEnum.hpp"
#include "src/ConfigFileReader.hpp"

namespace Actor
{
	enum class ActorTypeEnum : uint8_t
	{
		NONE = 0,
		PLAYER,
		ENEMY,
		BULLET,
		TILE
	};

	class ActorType : public Tools::SmartEnum<ActorTypeEnum>
	{
	public:

		ActorType();
		ActorType(ActorTypeEnum value);
		virtual ~ActorType() = default;

		std::string toString() override;
	};
}