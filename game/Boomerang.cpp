#include "Boomerang.h"
#include "Utils.h"
#include "Game.h"

Boomerang::Boomerang()
{
	SetAnimation(BOOMERANG_ANI_ID);
	die = true;
}

void Boomerang::Init(float x, float y, int nx)
{
	die = false;
	inUse = true;
	SetPosition(x, y);
	this->nx = nx;
	vx = nx * BOOMERANG_SPEED_VX;
	vy = -BOOMERANG_SPEED_VY;
	grid_->Move(this, x, y);
}


void Boomerang::StartAnimate()
{
	if (animateTimeStart == 0)
		animateTimeStart = GetTickCount64();
}

bool Boomerang::GetBackToPool()
{
	if (!inUse) return false;
	else if (die)
	{
		inUse = false;
		animateTimeStart = 0;
		return true;
	}
	return false;
}


void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	StartAnimate();

	x += dx;
	y += dy;

	if (GetTickCount64() - animateTimeStart > BOOMERANG_TIME_DIE) {
		die = true;
	}
	else if (GetTickCount64() - animateTimeStart > BOOMERANG_TIME_RETURN)
	{
		vx = -nx * BOOMERANG_SPEED_VX;
		vy = BOOMERANG_SPEED_VY;
	}

	grid_->Move(this, x, y);
}

void Boomerang::Render()
{
	animation_set->at(0)->Render(x, y, -nx, ny);
}

void Boomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BOOMERANG_BBOX_SIZE;
	b = y + BOOMERANG_BBOX_SIZE;
}