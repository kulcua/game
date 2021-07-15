#pragma once
#include "MarioState.h"
#define MARIO_WIDTH 48
#define MARIO_HEIGHT 48

class MarioDieState : public MarioState
{
	static MarioDieState* __instance;
	ULONGLONG dieTimeStart;
public:
	static MarioDieState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
	void StartDieTime() { dieTimeStart = GetTickCount64(); }
};
