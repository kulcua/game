#pragma once
#include "MarioState.h"

class MarioJumpingState : public MarioState
{
	static MarioJumpingState* __instance;
public:
	static MarioJumpingState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
};

