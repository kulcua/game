#include "Three.h"
#include "Utils.h"
#include "Game.h"

Three::Three(Curtain* curtain)
{
	SetAnimation(THREE_ANI_ID);
	vy = -0.2f;
	this->curtain = curtain;
	die = true;
}

void Three::Render()
{
	animation_set->at(0)->Render(x, y, nx, ny);
	//RenderBoundingBox();
}

void Three::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (vy == 0) {
		isStop = true;
	}
	vy = curtain->vy;
	y += dy;
}

void Three::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x;
	b = y;
}
