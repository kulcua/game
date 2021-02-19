#pragma once
#include "MarioDroppingState.h"

class MarioDropFlyState : public MarioDroppingState
{
	static MarioDropFlyState* __instance;
public:
	static MarioDropFlyState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
};

