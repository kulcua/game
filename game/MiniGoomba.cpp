#include "MiniGoomba.h"
#include "Utils.h"
#include "Game.h"
#include "MiniGoombaPool.h"

MiniGoomba::MiniGoomba()
{
	SetAnimation(MINI_GOOMBA_ANI_ID);
	die = true;
}

void MiniGoomba::Init(float x, float y)
{
	die = false;
	inUse = true;
	SetPosition(x, y);
	grid_->Move(this, x, y);
	timeToDie = GetTickCount64();
}


void MiniGoomba::StartAnimate()
{
	if (animateTimeStart == 0)
		animateTimeStart = GetTickCount64();
}

bool MiniGoomba::GetBackToPool()
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


void MiniGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	StartAnimate();

	vy = 0.1f;

	vx = nx * 0.2f;

	x += dx;
	y += dy;

	if (GetTickCount64() - timeToDie > MINI_GOOMBA_TIME_DIE)
		die = true;

	if (GetTickCount64() - timeFlip > MINI_GOOMBA_TIME_FLIP)
	{
		timeFlip = GetTickCount64();
		nx = -nx;
	}

	grid_->Move(this, x, y);
}

void MiniGoomba::Render()
{
	animation_set->at(0)->Render(x, y, -nx, ny);
}

void MiniGoomba::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MINI_GOOMBA_BBOX_SIZE;
	b = y + MINI_GOOMBA_BBOX_SIZE;
}