#include "MarioState.h"
#include "Mario.h"

void MarioState::GetBoundingBox(CMario &mario, float& left, float& top, float& right, float& bottom)
{
	left = mario.x;
	top = mario.y;

	if (mario.GetLevel() == MARIO_LEVEL_BIG)
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
