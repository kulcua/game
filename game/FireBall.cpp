#include "FireBall.h"
#include "Utils.h"

CFireBall::CFireBall(CMario* player, CPlant *plant)
{
	this->player = player;
	this->plant = plant;		
	SetPosition(plant->x, plant->y);
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!die)
	{
		CGameObject::Update(dt, coObjects);

		float x_mario, y_mario, x_plant, y_plant;

		player->GetPosition(x_mario, y_mario);
		plant->GetPosition(x_plant, y_plant);

		nx = plant->nx;

		if (plant->isUp)
			vy = -FIREBALL_SPEED;
		else
			vy = FIREBALL_SPEED;

		if (abs(x_mario - x_plant) < FIREBALL_CHECK_POS_SHOOT_X)
			vx = FIREBALL_SPEED * nx;
		else
			vx = FIREBALL_SPEED * nx * 2;

		x += dx;
		y += dy;

		if (abs(y_mario - y) > FIREBALL_CHECK_Y || abs(x_plant - x_mario) > FIREBALL_CHECK_X)
			die = true;
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