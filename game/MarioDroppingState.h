#pragma once
#include "MarioJumpingState.h"

class MarioDroppingState : public MarioJumpingState
{
	static MarioDroppingState* __instance;
public:
	static MarioDroppingState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
};
