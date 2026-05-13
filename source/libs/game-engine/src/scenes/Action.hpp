#pragma once

#include "ActionType.hpp"

namespace Scene
{
	class Action
	{
		ActionState mState;
		ActionType mType;

	public:
		Action();
		Action(ActionStateEnum actionState, ActionTypeEnum actionType);
		~Action() = default;

		ActionTypeEnum getType();
		ActionStateEnum getState();
	};
}