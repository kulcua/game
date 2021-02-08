#pragma once
#include "MarioState.h"
#include "Mario.h"

class MarioJumpingState : public MarioState
{
public:
	virtual MarioState* HandleInput(CMario& mario, int keyCode);
	virtual void Update(CMario& mario);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
};

