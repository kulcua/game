#pragma once 
#include "MarioState.h"
#include "Mario.h"
#include "MarioOnGroundState.h"

class MarioIdleState : public MarioOnGroundState
{
public:
	virtual MarioState* HandleInput(CMario& mario, int keyCode);
	virtual void Update(CMario& mario);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual void enter(CMario& mario)
	{
		//heroine.setGraphics(IMAGE_STAND);
	}
};

