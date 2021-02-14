#pragma once

#include "MarioState.h"

class MarioOnGroundState : public MarioState
{
public:
	//static MarioStandingState standing;
	virtual void HandleInput(CMario& mario);
	virtual void Update(CMario& mario) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual void Enter(CMario& mario) {};
};

