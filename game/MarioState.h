#pragma once
class CMario;
class MarioStandingState;

//#include "MarioStandingState.h"
//#include "Game.h"

class MarioState
{
	CMario* mario_;
	MarioStandingState* marioStandingState_;
public:
	// static state don’t burn memory and CPU cycles allocating objects each state change
	static MarioStandingState standing;
	//static MarioWalkingState walking;
	//static MarioJumpingState jumping;
	//static MarioDuckingState ducking;

	virtual void HandleInput(CMario& mario) {};
	virtual void Update(CMario& mario) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual void Render() {};

	// using Enter() method to set animation for each state
	virtual void Enter(CMario& mario)
	{
		//mario.setGraphics(IMAGE_STAND);
	}

	virtual ~MarioState() {}
};

