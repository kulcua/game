#pragma once 
#include "MarioState.h"

class MarioTailHitState : public MarioState
{
	static MarioTailHitState* __instance;
	DWORD hitStartTime;
public:
	static MarioTailHitState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
	void StartHit() { hitStartTime = GetTickCount64(); };
};