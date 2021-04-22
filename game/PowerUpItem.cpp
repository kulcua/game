#include "PowerUpItem.h"
#include "Animations.h"
#include "Mario.h"

PowerUpItem::PowerUpItem()
{
	mario = CMario::GetInstance();
}

void PowerUpItem::SetAnimation(int ani)
{
	this->ani = ani;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ani);
	SetAnimationSet(ani_set);
}

void PowerUpItem::UpdateMushroom(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (outBrick)
	{
		vy += ITEM_GRAVITY * dt;
		vx = ITEM_RED_MR_VX;
	}
	else vy = -ITEM_RED_MR_VY;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (state != MARIO_STATE_DIE)
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

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
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

	if (ani == 0)
	{
		startY = y;

		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
			SetAnimation(RED_MUSHROOM_ANI_ID);
		else
		{
			SetAnimation(LEAF_ANI_ID);
			vy = -LEAF_DEFLECT_SPEED;
		}
	}

	if (y < startY - ITEM_BBOX_HEIGHT && outBrick == false)
	{
		outBrick = true;
	}
	
	if (ani == RED_MUSHROOM_ANI_ID)
	{
		UpdateMushroom(dt, coObjects);
	}
	else UpdateLeaf(dt, coObjects);
}

void PowerUpItem::Render()
{
	CItem::Render();
}
