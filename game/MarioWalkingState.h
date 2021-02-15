#pragma once
#include "MarioOnGroundState.h"

class MarioWalkingState : public MarioOnGroundState
{
	static MarioWalkingState* __instance;
public:
	static MarioWalkingState* GetInstance();
	void HandleInput(CMario& mario);
	virtual void Update(CMario& mario);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
};

