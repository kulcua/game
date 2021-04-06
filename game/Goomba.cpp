#include "Goomba.h"
#include "Utils.h"

#define GOOMBA_DIE_TIME 200

CGoomba::CGoomba()
{
	SetState(GOOMBA_STATE_WALKING);
	die = false;
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!die)
	{
		CGameObject::Update(dt, coObjects);

		vy += GOOMBA_GRAVITY * dt;

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
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;

			if (nx != 0) vx = -vx;
			if (ny != 0) vy = 0;
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CGoomba::Render()
{
	int ani;
	if (!die)
	{
		ani = GOOMBA_ANI_WALKING;	
		animation_set->at(ani)->Render(x, y, nx);
	}
	else if (GetTickCount64() - die_time_start <= GOOMBA_DIE_TIME)
	{
		ani = GOOMBA_ANI_DIE;
		animation_set->at(ani)->Render(x, y, nx);
	}
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
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
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
	}
}
