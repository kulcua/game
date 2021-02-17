#pragma once
#include "MarioOnGroundState.h"

class MarioStoppingState : public MarioOnGroundState
{
	static MarioStoppingState* __instance;
public:
	static MarioStoppingState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
};

