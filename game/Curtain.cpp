#include "Curtain.h"
#include "Utils.h"

Curtain::Curtain()
{
	SetAnimation(CURTAIN_ANI_ID);
	SetPosition(0, 0);
	vy = -0.2f;
}

void Curtain::Render()
{
	//RenderBoundingBox();
}

void Curtain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	y += dy;
}

void Curtain::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x;
	b = y;
}
