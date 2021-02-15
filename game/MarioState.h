#pragma once

//class CMario;
class MarioStandingState;
class MarioWalkingState;
class MarioJumpingState;
class MarioDuckingState;

//#include "Mario.h"
//#include "MarioStandingState.h"

class MarioState
{
	friend class CMario;
public:
	//CMario* mario_;
	
	// static state don’t burn memory and CPU cycles allocating objects each state change
	static MarioStandingState standing;
	static MarioWalkingState walking;
	static MarioJumpingState jumping;
	static MarioDuckingState ducking;

	virtual void HandleInput(CMario& mario) = 0;
	virtual void Update(CMario& mario) = 0;
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);

	// using Enter() method to set animation for each state
	virtual void Enter(CMario& mario) = 0;
};

