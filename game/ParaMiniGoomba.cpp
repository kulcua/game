#include "ParaMiniGoomba.h"
#include "EffectPool.h"
#include "Game.h"
#include "Mario.h"
#include "MiniGoombaPool.h"

ParaMiniGoomba::ParaMiniGoomba()
{
	SetState(PARAMINIGOOMBA_STATE_WALK);
	level = PARAGOOMBA_LEVEL_WING;
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
}

void ParaMiniGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGoomba::Update(dt, coObjects);

	vx = nx * PARAMINIGOOMBA_VX_SPEED;
	if (abs(x - mario->x) > PARAMINIGOOMBA_MAX_X_TO_MARIO)
	{
		if (x - mario->x > 0)
			nx = -1;
		else nx = 1;
	}

	if (level == PARAGOOMBA_LEVEL_WING)
		ChangeState();
}

void ParaMiniGoomba::ChangeState()
{
	int timePassed = GetTickCount64() - timeStart;
	if (timePassed < PARAMINIGOOMBA_TIME_WALK)
	{
		SetState(PARAMINIGOOMBA_STATE_WALK);
	}
	else 
	{	
		SetState(PARAMINIGOOMBA_STATE_FLY);

		float dy = abs(y - mario->y);

		if (maxY == false)
		{
			vy = -PARAMINIGOOMBA_VY_THROW_SPEED;
		}

		if (dy >= PARAMINIGOOMBA_MAX_Y_TO_MARIO)
		{
			maxY = true;

			if (timeThrowStart == 0)
				timeThrowStart = GetTickCount64();

			int timeThrowRemain = GetTickCount64() - timeThrowStart;

			int timeNeed = (PARAMINIGOOMBA_MAX_THROW_TIME - throwGoombaTimes) * PARAMINIGOOMBA_TIME_SPACE_THROW;

			if (timeThrowRemain > timeNeed && MiniGoombaPool::GetInstance()->CheckNumberInPool() == throwGoombaTimes)
			{
				MiniGoomba* miniGoomba = MiniGoombaPool::GetInstance()->Create();
				if (miniGoomba != NULL)
				{
					miniGoomba->Init(x, y);
				}

				throwGoombaTimes--;

				if (throwGoombaTimes == 0)
				{
					throwGoombaTimes = PARAMINIGOOMBA_MAX_THROW_TIME;
					timeStart = GetTickCount64();
					timeThrowStart = 0;
				}
			}
		}
		else if (dy <= PARAMINIGOOMBA_MIN_Y_TO_MARIO)
		{
			maxY = false;
		}
	}
}

void ParaMiniGoomba::Render()
{
	int ani;
	if (dieTimeStart > 0)
	{
		ani = PARAGOOMBA_ANI_DIE;
	}
	else if (level == PARAGOOMBA_LEVEL_WING)
	{
		if (state == PARAMINIGOOMBA_STATE_WALK)
			ani = PARAGOOMBA_ANI_WALKING;
		else
			ani = PARAGOOMBA_ANI_FLYING;
	}
	else ani = PARAGOOMBA_ANI_NO_WING;
	animation_set->at(ani)->Render(x, y, nx, ny);
}

void ParaMiniGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
	{
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		StartDieTime();
		vx = 0;
		vy = 0;
		Effect* effect = EffectPool::GetInstance()->Create();
		if (effect != NULL)
			effect->InitPoint(EffectPoint::p100, x, y);
	}
	break;
	}
}