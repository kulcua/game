#pragma once
#include "MarioState.h"
#include "MarioOnGroundState.h"

class MarioWalkingState : public MarioOnGroundState
{
public:
	virtual MarioState* HandleInput(CMario& mario, int keyCode);
	virtual void Update(CMario& mario);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
};

