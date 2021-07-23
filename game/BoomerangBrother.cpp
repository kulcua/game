#include "BoomerangBrother.h"
#include "Mario.h"
#include "Game.h"
#include "BrotherBound.h"
#include "BoomerangPool.h"
#include "EffectPool.h"
#include "Ground.h"

BoomerangBrother::BoomerangBrother()
{
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	moveDirect = -1;
	SetState(BOOMERANG_BROTHER_STATE_WALK);
	timeStart = GetTickCount64();
}

void BoomerangBrother::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BOOMERANG_BROTHER_BBOX_WIDTH;
	b = y + BOOMERANG_BROTHER_BBOX_HEIGHT;
}

void BoomerangBrother::HandleCollision(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float nx, ny;
		FilterCollision(coEvents, coEventsResult, nx, ny);

		for (size_t i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<BrotherBound*>(e->obj))
			{
				if (e->nx)
				{
					moveDirect = -moveDirect;
					vx = moveDirect * BOOMERANG_BROTHER_WALK_SPEED;
				}
			}
			else if (dynamic_cast<Boomerang*>(e->obj))
			{
				e->obj->die = true;
			}
		}
	}
	for (size_t i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void BoomerangBrother::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vy += BOOMERANG_BROTHER_GRAVITY * dt;

	if (mario->x > x)
		nx = 1;
	else nx = -1;

	HandleCollision(coObjects);

	ChangeState();

	if (GetTickCount64() - dieTimeStart > ENERMY_DIE_TIME && dieTimeStart > 0)
	{
		dieTimeStart = 0;
		die = true;
	}
}

void BoomerangBrother::Render()
{
	int ani;
	if (state == BOOMERANG_BROTHER_STATE_THROW)
		ani = BOOMERANG_BROTHER_ANI_THROW;
	else ani = 0;
	animation_set->at(ani)->Render(x, y, nx, ny);
}

void BoomerangBrother::ChangeState()
{
	ULONGLONG timeMoving = GetTickCount64() - timeStart;
	ULONGLONG timeThrowing = GetTickCount64() - timeThrowStart;

	if (timeMoving < BOOMERANG_BROTHER_TIME_WALK_START)
		SetState(BOOMERANG_BROTHER_STATE_WALK);
	else if (timeMoving < BOOMERANG_BROTHER_TIME_THROW_START)
	{
		if (timeThrowStart == 0)
		{
			timeThrowStart = GetTickCount64();
		}
		else if (throwTimes > 0 && timeThrowing > BOOMERANG_BROTHER_TIME_THROW) {
			timeThrowStart = 0;
			Boomerang* boom = BoomerangPool::GetInstance()->Create();
			if (boom != NULL)
			{
				boom->Init(x, y, nx);
			}
			throwTimes--;
			if (throwTimes == 0)
				throwTimes = BOOMERANG_BROTHER_THROW_TIMES;
		}
		
	}
	else if (timeMoving < BOOMERANG_BROTHER_TIME_WALK_START*2)
		SetState(BOOMERANG_BROTHER_STATE_WALK);
	else {
		timeStart = GetTickCount64();
		SetState(BOOMERANG_BROTHER_STATE_JUMP);
	}
}

void BoomerangBrother::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOOMERANG_BROTHER_STATE_WALK:
	{
		vx = moveDirect * BOOMERANG_BROTHER_WALK_SPEED;
	}
	break;
	case BOOMERANG_BROTHER_STATE_JUMP:
	{
		vy = -BOOMERANG_BROTHER_JUMP_SPEED;
	}
	break;
	case BOOMERANG_BROTHER_STATE_DIE:
	{
		Effect* effect = EffectPool::GetInstance()->Create();
		if (effect != NULL)
			effect->InitPoint(EffectPoint::p100, x, y);
		StartDieTime();
		BeingKicked();
		break;
	}
	}
}