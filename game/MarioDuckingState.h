#pragma once
#include "MarioState.h"

class MarioDuckingState : public MarioState
{
public:
	virtual MarioState* HandleInput(CMario& mario);
	virtual void Update(CMario& mario);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
};

