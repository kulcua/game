#pragma once
#include "MarioOnGroundState.h"

class MarioRunningState : public MarioOnGroundState
{
	static MarioRunningState* __instance;
	int chargeTime_;
public:
	static MarioRunningState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
};
