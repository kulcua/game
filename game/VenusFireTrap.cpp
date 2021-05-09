#include "VenusFireTrap.h"
#include "FireBall.h"
#include "FireBallPool.h"

VenusFireTrap::VenusFireTrap(float y, int type) : CPlant(y)
{
	pool = FireBallPool::GetInstance();
	this->type = type;
}

void VenusFireTrap::FindPositionForShooting()
{
	if (shootingTime == false)
	{
		if (y < startY - PLANT_HEIGHT) // have not overlap with pipe
		{
			vy = 0.0f;
			StartShootTime();
		}
	}
	else if (GetTickCount64() - shootTimeStart > VENUS_SHOOT_TIME)
	{
		shootTimeStart = 0;
		shootingTime = false;
		vy = PLANT_SPEED;
	}
}

void VenusFireTrap::SetDirectionShootingFollowMario()
{
	float x_mario, y_mario;
	mario->GetPosition(x_mario, y_mario);
	if (x_mario < x)
		nx = -1;
	else
		nx = 1;

	if (shootingTime == false)
	{
		if (y_mario > y)
			isUp = false;
		else if (y_mario < y)
			isUp = true;
	}
}

void VenusFireTrap::StartShootTime()
{
	shootingTime = true;
	shootTimeStart = GetTickCount64();
	createFireball = true;
}

void VenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CPlant::Update(dt, coObjects);

	if (createFireball) // check shoot only 1 fireball
	{
		CFireBall* fireBall = pool->Create();
		if (fireBall != NULL)
		{
			fireBall->InitForPlant(this);
		}
	}

	SetDirectionShootingFollowMario();

	FindPositionForShooting();
}

void VenusFireTrap::Render()
{
	int ani = 0;
	if (shootingTime == false)
	{
		if (isUp)
			ani = VENUS_ANI_UP;
		else
			ani = VENUS_ANI_DOWN;
	}
	else
	{
		if (isUp)
			ani = VENUS_ANI_SHOOT_UP;
		else ani = VENUS_ANI_SHOOT_DOWN;
	}
	animation_set->at(ani)->Render(x, y, nx);
}