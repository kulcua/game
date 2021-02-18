#pragma once 
#include "MarioOnGroundState.h"

class MarioFlyingState : public MarioState
{
	static MarioFlyingState* __instance;
public:
	static MarioFlyingState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
};