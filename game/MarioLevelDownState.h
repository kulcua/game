#pragma once 
#include "MarioState.h"

class MarioLevelDownState : public MarioState
{
	static MarioLevelDownState* __instance;
	DWORD levelDownStartTime;
public:
	static MarioLevelDownState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
	void StartLevelDown();
};

