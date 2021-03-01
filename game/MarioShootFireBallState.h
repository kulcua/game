#pragma once 
#include "MarioAttackState.h"

class MarioShootFireBallState : public MarioAttackState
{
	static MarioShootFireBallState* __instance;
	DWORD hit_time_start;
public:
	static MarioShootFireBallState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
	void StartHit() { hit_time_start = GetTickCount64(); };
};