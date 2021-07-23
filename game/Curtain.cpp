#include "Curtain.h"
#include "Utils.h"

Curtain::Curtain()
{
	SetAnimation(CURTAIN_ANI_ID);
	SetPosition(0, 0);
	vy = -0.2f;
	ani = CURTAIN_ANI_RED;
}

void Curtain::Render()
{
	animation_set->at(ani)->Render(x, y, nx, ny);
	//RenderBoundingBox();
}

void Curtain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (y > 0) {
		vy = 0;
		y = 0;
	}

	y += dy;
}

void Curtain::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x;
	b = y;
}
