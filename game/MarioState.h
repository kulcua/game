#pragma once
#include "MarioStandingState.h"
#include "MarioWalkingState.h"
#include "MarioJumpingState.h"
#include "MarioDuckingState.h"
#include "Game.h"

class MarioState
{
protected:
	CGame* game = CGame::GetInstance();
public:
	// static state don’t burn memory and CPU cycles allocating objects each state change
	static MarioStandingState standing;
	//static MarioWalkingState walking;
	//static MarioJumpingState jumping;
	//static MarioDuckingState ducking;

	virtual MarioState* HandleInput(CMario& mario) {};
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

