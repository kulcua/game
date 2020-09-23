#include "Goomba.h"
#include "Utils.h"

#define GOOMBA_DIE_TIME 500

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

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (!die)
	{
		CGameObject::Update(dt, coObject);

		//TO-DO: make sure Goomba can interact with the world and to each of them too!

		x += dx;
		y += dy;

		if (vx < 0 && x < 0)
		{
			x = 0; vx = -vx;
		}

		if (vx > 0 && x > 290)
		{
			x = 290; vx = -vx;
		}
	}
	else return;
}

void CGoomba::Render()
{
	int ani;
	if (!die)
	{
		ani = GOOMBA_ANI_WALKING;	
		animation_set->at(ani)->Render(x, y, nx);
	}
	else if (GetTickCount() - die_time_start <= GOOMBA_DIE_TIME)
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
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1; //???
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
	}
}
