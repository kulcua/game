#include "MiniGoomba.h"
#include "Utils.h"
#include "Game.h"
#include "MiniGoombaPool.h"
#include "MarioJumpingState.h"

MiniGoomba::MiniGoomba()
{
	SetAnimation(MINI_GOOMBA_ANI_ID);
	die = true;
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
}

void MiniGoomba::Init(float x, float y)
{
	die = false;
	inUse = true;
	SetPosition(x, y);
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
	coObjects->push_back(this);

	CGameObject::Update(dt);

	StartAnimate();

	if (folowMario)
	{
		FollowMario();
	}
	else {
		vy = MINI_GOOMBA_SPEED_VY;
		vx = nx * MINI_GOOMBA_SPEED_VX;

		x += dx;
		y += dy;

		if (GetTickCount64() - timeToDie > MINI_GOOMBA_TIME_DIE)
			die = true;

		if (GetTickCount64() - timeFlip > MINI_GOOMBA_TIME_FLIP)
		{
			timeFlip = GetTickCount64();
			nx = -nx;
		}
	}
}

void MiniGoomba::Render()
{
	animation_set->at(0)->Render(x, y, nx, ny);
}

void MiniGoomba::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MINI_GOOMBA_BBOX_SIZE;
	b = y + MINI_GOOMBA_BBOX_SIZE;
}

void MiniGoomba::FollowMario()
{
	float l, t, r, b;
	mario->GetBoundingBox(l, t, r, b);
	b -= MINI_GOOMBA_BBOX_SIZE;
	if (x > r)
	{
		vx = -MINI_GOOMBA_SPEED_VX_FL_MARIO;
		x = r;
	}
	else if (x < l)
	{
		vx = MINI_GOOMBA_SPEED_VX_FL_MARIO;
		x = l;
	}
	if (y > b)
	{
		vy = -MINI_GOOMBA_SPEED_VY_FL_MARIO;
		y = b;
	}
	else if (y < t)
	{
		vy = MINI_GOOMBA_SPEED_VY_FL_MARIO;
		y = t;
	}

	MarioJumpingState::GetInstance()->isHighJump = false;
	x += dx;
	y += dy;
}