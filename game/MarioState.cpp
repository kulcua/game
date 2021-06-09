#include "MarioState.h"
#include "Mario.h"
#include "MarioStandingState.h"

void MarioState::Update(CMario& mario, DWORD dt)
{
	if (mario.vx == 0)
	{
		mario.state_ = MarioState::standing.GetInstance();
	}
	else if (mario.IsAutoMoving() == false) {
		if (mario.vx > 0)
		{
			mario.vx += -MARIO_ACCELERATION * dt;
			if (mario.vx < 0)
				mario.vx = 0;
		}
		else
		{
			mario.vx += MARIO_ACCELERATION * dt;
			if (mario.vx > 0)
				mario.vx = 0;
		}
	}
}

void MarioState::GetBoundingBox(CMario &mario, float& left, float& top, float& right, float& bottom)
{
	left = mario.x;
	top = mario.y;

	if (mario.GetLevel() == MARIO_LEVEL_BIG || mario.GetLevel() == MARIO_LEVEL_FIRE)
	{
		right = mario.x + MARIO_BIG_BBOX_WIDTH;
		bottom = mario.y + MARIO_BIG_BBOX_HEIGHT;
	}
	else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
	{
		right = mario.x + MARIO_RACCOON_BBOX_WIDTH;
		bottom = mario.y + MARIO_RACCOON_BBOX_HEIGHT;
	}
	else
	{
		right = mario.x + MARIO_SMALL_BBOX_WIDTH;
		bottom = mario.y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

