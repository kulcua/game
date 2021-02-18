#pragma once
#include "Utils.h"
class MarioStandingState;
class MarioWalkingState;
class MarioJumpingState;
class MarioDuckingState;
class MarioStoppingState;

class MarioState
{
	friend class CMario;
public:
	// static state don’t burn memory and CPU cycles allocating objects each state change
	static MarioStandingState standing;
	static MarioWalkingState walking;
	static MarioJumpingState jumping;
	static MarioDuckingState ducking;
	static MarioStoppingState stopping;

	virtual void HandleInput(CMario& mario, Input input) = 0;
	virtual void Update(CMario& mario, DWORD dt) = 0;
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);

	// using Enter() method to set animation for each state
	virtual void Enter(CMario& mario) = 0;
};

