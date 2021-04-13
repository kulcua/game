#include "ParaGoomba.h" 

ParaGoomba::ParaGoomba()
{
	SetState(PARAGOOMBA_STATE_LOW_JUMP);
	die = false;
	level = PARAGOOMBA_MAX_LEVEL;
	jumpTimes = PARAGOOMBA_JUMP_TIMES;
	mario = CMario::GetInstance();
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
		if (level == PARAGOOMBA_MAX_LEVEL)
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

	if (die == false)
	{
		vx = -GOOMBA_WALKING_SPEED;

		if (level == PARAGOOMBA_MAX_LEVEL)
		{
			if (jumpTimes > 0 && isOnGround)
			{
				SetState(PARAGOOMBA_STATE_LOW_JUMP);
				if (jumpTimes == 0)
				{
					vy = -PARAGOOMBA_HIGH_JUMP_SPEED;
					StartWalkingTime();
				}
			}

			if (GetTickCount64() - walkingTimeStart > PARAGOOMBA_WALK_TIME && walkingTimeStart > 0)
			{
				walkingTimeStart = 0;
				jumpTimes = PARAGOOMBA_JUMP_TIMES;
			}
		}
	}
}

void ParaGoomba::Render()
{
	int ani;
	if (!die)
	{
		if (level == PARAGOOMBA_MAX_LEVEL)
		{
			if (isOnGround)
				ani = PARAGOOMBA_ANI_WALKING;
			else
				ani = PARAGOOMBA_ANI_FLYING;
		}
		else ani = PARAGOOMBA_ANI_NO_WING;
		animation_set->at(ani)->Render(x, y, nx);
	}
	else if (dieTimeStart > 0)
	{
		ani = PARAGOOMBA_ANI_DIE;
		animation_set->at(ani)->Render(x, y, nx);
	}
	//RenderBoundingBox();
}

void ParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		StartDieTime();
		vx = 0;
		vy = 0;
		break;
	case PARAGOOMBA_STATE_LOW_JUMP:
		vy = -PARAGOOMBA_LOW_JUMP_SPEED;
		isOnGround = false;
		jumpTimes--;
		break;
	}
}