#pragma once
#include "MarioState.h"

class MarioOnGroundState : public MarioState
{
public:
	MarioState* HandleInput(CMario& mario);
	virtual void Update(CMario& mario) = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Render() = 0;
	virtual void Enter(CMario& mario) = 0;
};

