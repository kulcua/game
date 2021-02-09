#pragma once 

#include "MarioOnGroundState.h"

class MarioStandingState : public MarioOnGroundState
{
public:
	virtual void HandleInput(CMario& mario);
	virtual void Update(CMario& mario);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual void Enter(CMario& mario);
};