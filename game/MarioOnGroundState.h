#pragma once
#include "MarioState.h"
#include "MarioAttackState.h"

class MarioOnGroundState : public MarioState
{
	friend class MarioAttackState;
public:
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt) {};
};
