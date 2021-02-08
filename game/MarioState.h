#pragma once
#include "Mario.h"
#include "MarioIdleState.h"
#include "MarioWalkingState.h"
#include "MarioJumpingState.h"
#include "MarioDuckingState.h"

class MarioState
{
public:
	static MarioIdleState idle;
	static MarioWalkingState walking;
	static MarioJumpingState jumping;
	static MarioDuckingState ducking;

	virtual MarioState* HandleInput(CMario& mario, int keyCode) {};
	virtual void Update(CMario& mario) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual void Render() {};

	virtual ~MarioState() {}
};

