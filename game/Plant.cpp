#include "Plant.h"
#include "Ground.h"
#include "Pipe.h"
#include "PlayScene.h"

CPlant::CPlant(float y) {
	startY = y;
	vy = -PLANT_SPEED;
	mario = CMario::GetInstance();
	pool = FireBallPool::GetInstance();
}

void CPlant::FindPositionForShooting()
{
	if (shootingTime == false)
	{
		if (y < startY - PLANT_HEIGHT) // have not overlap with pipe
		{
			vy = 0.0f;
			StartShootTime();
		}
	}
	else if (GetTickCount64() - shootTimeStart > PLANT_SHOOT_TIME)
	{
		shootTimeStart = 0;
		shootingTime = false;
		vy = PLANT_SPEED;
	}
}

void CPlant::SetDirectionShootingFollowMario()
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

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!die)
	{
		CGameObject::Update(dt, coObjects);

		y += dy;

		if (y > startY && vy > 0)
			vy = -vy;

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
}

void CPlant::Render()
{
	if (die == false)
	{
		int ani = 0;
		if (shootingTime == false)
		{
			if (isUp)
				ani = PLANT_ANI_UP;
			else
				ani = PLANT_ANI_DOWN;
		}
		else
		{
			if (isUp)
				ani = PLANT_ANI_SHOOT_UP;
			else ani = PLANT_ANI_SHOOT_DOWN;
		}		
		animation_set->at(ani)->Render(x, y, nx);
	}
	//RenderBoundingBox();
}

void CPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PLANT_WIDTH;
	b = y + PLANT_HEIGHT;
}

