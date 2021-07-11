#pragma once 
#include "MarioState.h"

class MarioShootFireBallState : public MarioState
{
	static MarioShootFireBallState* __instance;
	ULONGLONG hitStartTime;
public:
	static MarioShootFireBallState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
	void StartHit() { hitStartTime = GetTickCount64(); };
};