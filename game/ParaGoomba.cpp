#include "ParaGoomba.h" 
#include "EffectPool.h"
#include "Game.h"

ParaGoomba::ParaGoomba()
{
	SetState(PARAGOOMBA_STATE_JUMP);
	level = GOOMBA_LEVEL_WING;
	jumpTimes = PARAGOOMBA_JUMP_TIMES;
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
}

void ParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else 
	{
		if (level == GOOMBA_LEVEL_WING)
		{
			if (isOnGround)
				bottom = y + PARAGOOMBA_BBOX_WALK_HEIGHT;
			else
				bottom = y + PARAGOOMBA_BBOX_FLY_HEIGHT;
		}
		else bottom = y + GOOMBA_BBOX_HEIGHT;
	}
}

void ParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGoomba::Update(dt, coObjects);

	if (level == GOOMBA_LEVEL_WING)
	{
		if (jumpTimes > 0 && isOnGround)
		{
			SetState(PARAGOOMBA_STATE_JUMP);
		}

		if (GetTickCount64() - walkingTimeStart > PARAGOOMBA_WALK_TIME && walkingTimeStart > 0)
		{
			walkingTimeStart = 0;
			jumpTimes = PARAGOOMBA_JUMP_TIMES;
		}
	}
}

void ParaGoomba::Render()
{
	int ani;
	if (dieTimeStart > 0)
	{
		ani = PARAGOOMBA_ANI_DIE;
	}
	else if (level == GOOMBA_LEVEL_WING)
	{
		if (isOnGround)
			ani = PARAGOOMBA_ANI_WALKING;
		else
			ani = PARAGOOMBA_ANI_FLYING;
	}
	else ani = PARAGOOMBA_ANI_NO_WING;
	animation_set->at(ani)->Render(x, y, nx, ny);
}

void ParaGoomba::SetState(int state)
{
	CGoomba::SetState(state);
	switch (state)
	{
		case PARAGOOMBA_STATE_JUMP:
		{
			jumpTimes--;
			isOnGround = false;
			if (jumpTimes == 0)
			{
				vy = -PARAGOOMBA_HIGH_JUMP_SPEED;
				StartWalkingTime();
			}
			else vy = -PARAGOOMBA_LOW_JUMP_SPEED;
			break;
		}
	}
}