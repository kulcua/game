#include "Goomba.h"
#include "Utils.h"
#include "Ground.h"

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

		if (x < 0) //coll with boundx
			die = true;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		//TO-DO: make sure Goomba can interact with the world and to each of them too!
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

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
			//if (rdx != 0 && rdx!=dx)
			//	x += nx*abs(rdx); 

			// block every object first!
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;

			//if (nx != 0) vx = 0;
			//if (ny != 0) vy = 0;
			//
			// Collision logic with other objects
			//
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CGround*>(e->obj))
				{
					if (e->nx)
					{
						vx = -vx;
					}			
				}
				else
				{
					x += dx;
					//DebugOut(L"not ground dx: %f x: %f\n", dx, x);
				}
			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		//x += dx;
		//y += dy;

		//if (vx < 0 && x < 0)
		//{
		//	x = 0; vx = -vx;
		//}

		//if (vx > 0 && x > 290)
		//{
		//	x = 290; vx = -vx;
		//}
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
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		StartDieTime();
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
	}
}
