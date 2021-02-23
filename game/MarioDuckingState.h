#pragma once
#include "MarioOnGroundState.h"

class MarioDuckingState : public MarioOnGroundState
{
	static MarioDuckingState* __instance;
	DWORD jumpStartTime;
public:
	static MarioDuckingState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
	void StartJump();
};

