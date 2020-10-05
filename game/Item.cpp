#include "Item.h"
#include "Utils.h"
#include "Brick.h"
#include "Pipe.h"
#include "BigBox.h"
#include "Ground.h"

CItem::CItem(int type, CMario *mario)
{
	this->type = type;
	isEnable = false;
	this->mario = mario;
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!die && isEnable)
	{
		CGameObject::Update(dt, coObjects);

		if (state == 0)
		{
			SetState(type);
		}

		if (isGravity)
		{
			vy += ITEM_GRAVITY * dt;
		}

		if (state == ITEM_STATE_COIN)
		{
			if (GetTickCount() - fly_time_start > ITEM_COIN_TIME)
			{
				die = true;
			}
		}
		else if (state == ITEM_STATE_RED_MUSHROOM)
		{
			if (!outBrick)
			{
				CollisionAABB(coObjects);
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

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// block every object first!
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;

			//DebugOut(L"vx: %f\n", vx);
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CPipe*>(e->obj))
				{
					if (e->nx)
					{
						vx = -ITEM_RED_MR_VX;
						DebugOut(L"vooo\n");
					}
				}
				//else
				//{
				//	x += dx;
				//}
			}
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CItem::CollisionAABB(vector<LPGAMEOBJECT>* coObjects) 
{
	int brick = 0;
	for (int i = 0; i < coObjects->size(); i++) //need filter to box
	{
		//tinh toan khi vang khoi brick
		if (dynamic_cast<CBrick*>(coObjects->at(i)))
		{
			if (AABB(coObjects->at(i)))
			{
				brick++;
			}
		}
	}	
	DebugOut(L"aabb\n");
	if (brick == 0)
	{
		isGravity = true;
		outBrick = true;
		vx = -ITEM_RED_MR_VX;
	}
	else {
		isGravity = false;
	}
}

void CItem::Render()
{
	if (isEnable && !die)
	{
		animation_set->at(0)->Render(x, y, NULL);
	}
	//RenderBoundingBox();
}

void CItem::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_COIN:
		vy = -ITEM_COIN_JUMP_SPEED;
		StartFlying();
		isGravity = true;
		break;
	case ITEM_STATE_RED_MUSHROOM:
		vy = -ITEM_RED_MR_VY;
		isGravity = false;
		//nx = -mario->nx;
		break;
	default:
		break;
	}
}

void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isEnable)
	{
		l = x;
		t = y;
		r = x + ITEM_BBOX_WIDTH;
		b = y + ITEM_BBOX_HEIGHT;
	}
}