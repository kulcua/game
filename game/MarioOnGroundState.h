#pragma once

#include "MarioState.h"

class MarioOnGroundState : public MarioState
{
public:
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt) {};
};

