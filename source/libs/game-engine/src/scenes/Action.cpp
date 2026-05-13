#pragma once

#include "Action.hpp"

namespace Scene
{	
	Action::Action() : mState(ActionStateEnum::NONE), mType(ActionTypeEnum::NONE) {};
	Action::Action(ActionStateEnum actionState, ActionTypeEnum actionType) : mState(actionState), mType(actionType) {}

	ActionTypeEnum Action::getType()
	{
		return mType.getEnum();
	}
	ActionStateEnum Action::getState()
	{
		return mState.getEnum();
	}
}