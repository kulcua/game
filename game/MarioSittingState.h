#pragma once
#include "MarioOnGroundState.h"

class MarioSittingState : public MarioOnGroundState
{
	static MarioSittingState* __instance;
	ULONGLONG jumpStartTime;
public:
	bool isSit;
	static MarioSittingState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
	void StartJump();
};

