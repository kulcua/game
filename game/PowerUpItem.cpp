#include "PowerUpItem.h"
#include "Animations.h"
#include "Mario.h"
#include "BigBox.h"
#include "Game.h"

PowerUpItem::PowerUpItem()
{
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	setItem = PowerUp::none;
	startY = 0;
	outBrick = false;
}

void PowerUpItem::UpdateMushroom(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (outBrick)
	{
		vy += ITEM_GRAVITY * dt;
		if (vx == 0)
			vx = ITEM_RED_MR_VX;
	}
	else vy = -ITEM_RED_MR_VY;

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
		float nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, nx, ny);

		for (size_t i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBigBox*>(e->obj))
			{
				CBigBox* box = dynamic_cast<CBigBox*>(e->obj);
				if (e->nx != 0)
				{
					vx = -nx * ITEM_RED_MR_VX;
					x += dx;
				}
			}
			else {
				if (e->nx != 0)
				{
					vx = nx * ITEM_RED_MR_VX;
				}
			}
		}
	}

	for (size_t i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void PowerUpItem::UpdateLeaf(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (outBrick)
		vy = ITEM_LEAF_DROP_SPEED;

	if (vx == 0)
	{
		nx = -nx;
		vx = nx * ITEM_LEAF_VX;
	}
	else if (vx > 0)
	{
		vx += -MARIO_ACCELERATION * dt;
		if (vx < 0)
			vx = 0;
	}
	else
	{
		vx += MARIO_ACCELERATION * dt;
		if (vx > 0)
			vx = 0;
	}

	x += dx;
	y += dy;
}

void PowerUpItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (setItem == PowerUp::none)
	{
		startY = y;

		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
		{
			SetAnimation(RED_MUSHROOM_ANI_ID);
			setItem = PowerUp::mushroom;
		}
		else
		{
			setItem = PowerUp::leaf;
			SetAnimation(LEAF_ANI_ID);
			vy = -LEAF_DEFLECT_SPEED;
		}
	}

	if (y < startY - ITEM_BBOX_HEIGHT && outBrick == false)
	{
		outBrick = true;
	}
	
	if (setItem == PowerUp::mushroom)
	{
		UpdateMushroom(dt, coObjects);
	}
	else UpdateLeaf(dt, coObjects);
}

void PowerUpItem::Render()
{
	if (setItem != PowerUp::none)
		CItem::Render();
}
