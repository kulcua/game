#pragma once 
#include "MarioJumpingState.h"

class MarioFlyingState : public MarioJumpingState
{
	static MarioFlyingState* __instance;
public:
	static MarioFlyingState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
};