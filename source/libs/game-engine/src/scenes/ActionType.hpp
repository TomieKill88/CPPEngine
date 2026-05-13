#pragma once

#include<cstdint>

#include "src/general/SmartEnum.hpp"

namespace Scene
{
	enum class ActionTypeEnum : uint8_t
	{
		NONE = 0,
		// player
		JUMP,
		RUN,
		SHOOT,
		SPECIAL,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		// system
		PAUSE,
		START,
		CANCEL,
		ACCEPT,
		SELECT
	};

	enum class ActionStateEnum : uint8_t
	{
		NONE = 0,
		// player
		START,
		END
	};

	class ActionType : public Tools::General::SmartEnum<ActionTypeEnum>
	{
	public:

		ActionType();
		ActionType(ActionTypeEnum value);
		virtual ~ActionType() = default;

		std::string toString() override;
	};

	class ActionState : public Tools::General::SmartEnum<ActionStateEnum>
	{
	public:

		ActionState();
		ActionState(ActionStateEnum value);
		virtual ~ActionState() = default;

		std::string toString() override;
	};
}