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
		float nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, nx, ny);
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void GreenMushroom::Render()
{
	CItem::Render();
}
