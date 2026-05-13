#include "ActionType.hpp"

namespace Scene
{
	ActionType::ActionType() : SmartEnum<ActionTypeEnum>(ActionTypeEnum::NONE)
	{
	}

	ActionType::ActionType(ActionTypeEnum value) : SmartEnum<ActionTypeEnum>(value)
	{
		setEnum(value);
	}


	std::string ActionType::toString()
	{
		std::string name = "";

		switch (mValue) {
		case (ActionTypeEnum::NONE):
			name = std::string("NONE");
			break;
		case (ActionTypeEnum::JUMP):
			name = std::string("JUMP");
			break;
		case (ActionTypeEnum::RUN):
			name = std::string("RUN");
			break;
		case (ActionTypeEnum::SHOOT):
			name = std::string("SHOOT");
			break;
		case (ActionTypeEnum::UP):
			name = std::string("UP");
			break;
		case (ActionTypeEnum::DOWN):
			name = std::string("DOWN");
			break;
		case (ActionTypeEnum::LEFT):
			name = std::string("LEFT");
			break;
		case (ActionTypeEnum::RIGHT):
			name = std::string("RIGHT");
			break;
		case (ActionTypeEnum::CANCEL):
			name = std::string("CANCEL");
			break;
		case (ActionTypeEnum::PAUSE):
			name = std::string("PAUSE");
			break;
		case (ActionTypeEnum::START):
			name = std::string("START");
			break;
		case (ActionTypeEnum::ACCEPT):
			name = std::string("ACCEPT");
			break;
		case (ActionTypeEnum::SELECT):
			name = std::string("SELECT");
			break;
		default:
			name = std::string("ENUMER");
			break;
		}
			
		return name;

	}

	ActionState::ActionState() : SmartEnum<ActionStateEnum>(ActionStateEnum::NONE)
	{
	}

	ActionState::ActionState(ActionStateEnum value) : SmartEnum<ActionStateEnum>(value)
	{
		setEnum(value);
	}


	std::string ActionState::toString()
	{
		std::string name = "";

		switch (mValue) {
		case (ActionStateEnum::NONE):
			name = std::string("NONE");
			break;
		case (ActionStateEnum::START):
			name = std::string("START");
			break;
		case (ActionStateEnum::END):
			name = std::string("END");
			break;
		default:
			name = std::string("ENUMER");
			break;
		}

		return name;

	}
}