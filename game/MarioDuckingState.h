#pragma once
#include "MarioOnGroundState.h"

class MarioDuckingState : public MarioOnGroundState
{
	static MarioDuckingState* __instance;
public:
	static MarioDuckingState* GetInstance();
	void HandleInput(CMario& mario);
	virtual void Update(CMario& mario);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
};

