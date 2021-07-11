#pragma once 
#include "MarioOnGroundState.h"

class MarioKickState : public MarioOnGroundState
{
	static MarioKickState* __instance;
	ULONGLONG kickStartTime;
public:
	static MarioKickState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
	void StartKick() { kickStartTime = GetTickCount64(); };
};