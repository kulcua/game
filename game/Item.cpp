#include "Item.h"
#include "Utils.h"
#include "Brick.h"
#include "Pipe.h"
#include "BigBox.h"
#include "Ground.h"

CItem::CItem(int type, CMario *mario)
{
	this->type = type;
	this->mario = mario;
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!die)
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
		else if (state == ITEM_STATE_LEAF)
		{
			if (GetTickCount() - fly_time_start > ITEM_LEAF_TIME)
			{
				vy = ITEM_LEAF_DROP_SPEED;
			}

			if (vx == 0)
			{
				nx = -nx;
				vx = -ITEM_LEAF_VX * nx;
			}
			else
			{
				float a;
				if (vx > 0)
				{
					a = -ITEM_LEAF_A;
					vx += a * dt;
					if (vx < 0)
						vx = 0;
				}
				else
				{
					a = ITEM_LEAF_A;
					vx += a * dt;
					if (vx > 0)
						vx = 0;
				}
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

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CPipe*>(e->obj))
				{
					if (e->nx)
					{
						vx = -ITEM_RED_MR_VX;
					}
				}
				else if (dynamic_cast<CGround*>(e->obj))
				{
					if (state == ITEM_STATE_LEAF)
					{
						die = true;
					}
				}
				else if (dynamic_cast<CBrick*>(e->obj))
				{
					if (state == ITEM_STATE_LEAF)
					{
						x += dx;
						y += dy;
					}
				}
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
		if (dynamic_cast<CBrick*>(coObjects->at(i)))
			if (state == ITEM_STATE_RED_MUSHROOM)
			{
				//tinh toan khi vang khoi brick
				if (AABB(coObjects->at(i)))
				{
					brick++;
				}
			}
	}
	//	else if (state == ITEM_STATE_LEAF)
	//	{
	//		if (dynamic_cast<CGround*>(coObjects->at(i)))
	//		{
	//			if (AABB(coObjects->at(i)))
	//			{
	//				die = true;
	//				DebugOut(L"die\n");
	//				break;
	//			}
	//		}
	//	}
	//}	
	//DebugOut(L"aabb\n");
	//set dieu kien sau khi check aabb
	if (state == ITEM_STATE_RED_MUSHROOM)
	{
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
}

void CItem::Render()
{
	if (!die)
	{
		animation_set->at(0)->Render(x, y, nx);
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
		break;
	case ITEM_STATE_LEAF:
		StartFlying();
		vx = ITEM_LEAF_VX;
		isGravity = false;
		break;
	default:
		break;
	}
}

void CItem::StartFlying()
{ 
	isFlying = true; 
	fly_time_start = GetTickCount(); 
	if (state == ITEM_STATE_LEAF)
		vy = -ITEM_COIN_JUMP_SPEED;
}

void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + ITEM_BBOX_WIDTH;
	b = y + ITEM_BBOX_HEIGHT;
}