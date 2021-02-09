#pragma once

#include "MarioState.h"

class MarioOnGroundState : public MarioState
{
public:
	virtual void HandleInput(CMario& mario);
	virtual void Update(CMario& mario) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual void Render() {};
	virtual void Enter(CMario& mario) {};
};

