#pragma once 
#include "MarioOnGroundState.h"

class MarioStandingState : public MarioOnGroundState
{
	static MarioStandingState* __instance;
public:
	static MarioStandingState* GetInstance();
	virtual void HandleInput(CMario& mario);
	virtual void Update(CMario& mario);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
};