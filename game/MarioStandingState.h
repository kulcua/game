#pragma once 
#include "MarioState.h"
#include "MarioOnGroundState.h"

class MarioStandingState : public MarioOnGroundState
{
public:
	virtual MarioState* HandleInput(CMario& mario);
	virtual void Update(CMario& mario);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual void Enter(CMario& mario);
};

