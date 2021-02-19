#pragma once 
#include "MarioState.h"

class MarioLevelUpState : public MarioState
{
	static MarioLevelUpState* __instance;
	DWORD level_up_time_start;
public:
	static MarioLevelUpState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
	void StartLevelUp() { level_up_time_start = GetTickCount64(); };
};
