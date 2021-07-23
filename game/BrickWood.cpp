#include "BrickWood.h"
#include "Utils.h"
#include "Game.h"
#include "Mario.h"

BrickWood::BrickWood(float startX)
{
	nDeflect = 0;
	item = NULL;
	this->startX = startX;
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	throwItem = false;
	SetAnimation(BRICK_WOOD_ANI_ID);
}

void BrickWood::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	if ((x < startX && nDeflect > 0) || (x > startX && nDeflect < 0))
	{
		vx += nDeflect * BRICK_WOOD_VX_RETURN;
	}
	else if (nDeflect != 0)
	{
		mario->vx = nDeflect * BRICK_WOOD_DEFLECT_MARIO_VX;
		x = startX;
		vx = 0;
		nDeflect = 0;
	}
}

void BrickWood::Deflect(float nx)
{
	if (nDeflect == 0)
	{
		if (throwItem == false)
		{
			item->die = false;
			throwItem = true;
		}
		nDeflect = nx;
		this->vx = -nDeflect * BRICK_WOOD_VX_DEFLECT;
	}
}

void BrickWood::Render()
{
	int ani = 0;
	if (nDeflect != 0)
		ani = BRICK_WOOD_ANI_DISABLE;
	else ani = BRICK_WOOD_ANI_WOOD;
	animation_set->at(ani)->Render(x, y, nx, ny);
}

void BrickWood::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_WOOD_BBOX_SIZE;
	b = y + BRICK_WOOD_BBOX_SIZE;
}