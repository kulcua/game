#include "BoomerangBrother.h"
#include "Mario.h"
#include "Game.h"
#include "BrotherBound.h"
#include "BoomerangPool.h"
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
		float min_tx, min_ty, nx, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (state != BOOMERANG_BROTHER_STATE_WALK)
			if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
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
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
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
}

void BoomerangBrother::Render()
{
	int ani = 0;
	if (state == BOOMERANG_BROTHER_STATE_THROW)
		ani = BOOMERANG_BROTHER_ANI_THROW;
	animation_set->at(ani)->Render(x, y, nx, ny);
}

void BoomerangBrother::ChangeState()
{
	int timePassed = GetTickCount64() - timeStart;
	if (timePassed < 3000)
		SetState(BOOMERANG_BROTHER_STATE_WALK);
	else if (timePassed < 3500)
	{
		SetState(BOOMERANG_BROTHER_STATE_THROW);
		if (BoomerangPool::GetInstance()->CheckBoomerangInPool(0) == false && BoomerangPool::GetInstance()->CheckBoomerangInPool(1) == false)
		{
			Boomerang* boom = BoomerangPool::GetInstance()->Create();
			if (boom != NULL)
			{
				boom->Init(x, y, nx);
			}
		}
	}
	else if (timePassed < 4500)
	{
		Boomerang* boom = BoomerangPool::GetInstance()->Create();
		if (boom != NULL)
		{
			boom->Init(x, y, nx);
		}
	}
	else if (timePassed < 7000)
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
	}
}