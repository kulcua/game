#include "GreenMushroom.h"
#include "Animations.h"

GreenMushroom::GreenMushroom(float y)
{
	startY = y;
	SetAnimation(GREEN_MUSHROOM_ANI_ID);
}

void GreenMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (y < startY - ITEM_BBOX_HEIGHT && outBrick == false)
	{
		outBrick = true;
	}

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

void GreenMushroom::Render()
{
	CItem::Render();
}
