#include "Koopas.h"
#include "Brick.h"
#include "Ground.h"
#include "BigBox.h"
#include "Utils.h"
#include "Pipe.h"

CKoopas::CKoopas()
{
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + KOOPAS_BBOX_WIDTH;
	if (state == KOOPAS_STATE_WALKING)
	{
		b = y + KOOPAS_BBOX_HEIGHT;
	}
	else
	{
		b = y + KOOPAS_BBOX_HEIGHT_DIE;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!die)
	{
		DebugOut(L"vx: %f vy: %f\n", vx, vy);
		CGameObject::Update(dt, coObjects);

		vy += KOOPAS_GRAVITY * dt;

		if (state != KOOPAS_STATE_BALL)
		{
			if (vx < 0 && x < 510)
			{
				x = 510;
				vx = -vx;
				nx = 1;
				DebugOut(L"left\n");
			}

			if (vx > 0 && x > 600) {
				x = 600;
				vx = -vx;
				nx = -1;
				DebugOut(L"right\n");
			}
		}
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

			if (ny != 0) vy = 0;

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj))
				{
					CBrick* brick = dynamic_cast<CBrick*>(e->obj);
					brick->SetState(BRICK_STATE_DISABLE);
					if (e->nx)
						vx = -vx;
				}
				else if (dynamic_cast<CGround*>(e->obj))
				{
					if (e->nx)
						vx = -vx;
				}
				else if (dynamic_cast<CPipe*>(e->obj))
				{
					if (e->nx)
						vx = -vx;
				}
				else if (dynamic_cast<CBigBox*>(e->obj))
				{
					x += dx;
				}
			}

		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CKoopas::Render()
{
	int ani;
	if (state == KOOPAS_STATE_DIE)
	{
		ani = KOOPAS_ANI_DIE;
	}
	else if (state == KOOPAS_STATE_BALL)
		ani = KOOPAS_ANI_BALL;
	else
		ani = KOOPAS_ANI_WALKING;

	animation_set->at(ani)->Render(x, y, nx);

	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE;
		break;
	case KOOPAS_STATE_BALL:
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE;
		vx = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = KOOPAS_WALKING_SPEED;
		break;
	}
}
