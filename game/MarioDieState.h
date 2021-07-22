#pragma once
#include "MarioState.h"

class MarioDieState : public MarioState
{
	static MarioDieState* __instance;
	ULONGLONG dieTimeStart = 0;
public:
	static MarioDieState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
	void StartDieTime() { dieTimeStart = GetTickCount64(); }
};
