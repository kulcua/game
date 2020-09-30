#include "FireBall.h"
#include "Utils.h"

CFireBall::CFireBall(CGameObject* plant)
{
	float x_plant, y_plant;
	plant->GetPosition(x_plant, y_plant);
	SetPosition(x_plant, y_plant);
	nx = plant->nx;
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!die)
	{
		CGameObject::Update(dt, coObjects);

		x += dx;
		y += dy;

		if (nx < 0)
			vx = -FIREBALL_SPEED;
		else vx = FIREBALL_SPEED;
	}
}

void CFireBall::Render()
{
	if (!die)
	{
		animation_set->at(0)->Render(x, y, NULL);
		//RenderBoundingBox();
	}
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREBALL_WIDTH;
	b = y + FIREBALL_HEIGHT;
}