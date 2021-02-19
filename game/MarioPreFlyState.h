#pragma once 
#include "MarioOnGroundState.h"

class MarioPreFlyState : public MarioOnGroundState
{
	static MarioPreFlyState* __instance;
public:
	static MarioPreFlyState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
};