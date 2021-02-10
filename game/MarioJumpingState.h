#pragma once
#include "MarioState.h"

class MarioJumpingState : public MarioState
{
public:
	virtual void Init() {};
	void HandleInput(CMario& mario);
	virtual void Update(CMario& mario);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
};

