#include "Plant.h"
#include "Ground.h"
#include "Pipe.h"
#include "PlayScene.h"

CPlant::CPlant() {
	//vy = -PLANT_SPEED;
	mario = CMario::GetInstance();
	pool = FireBallPool::GetInstance();
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!die)
	{
		//DebugOut(L"vy %f\n", vy);
		CGameObject::Update(dt, coObjects);

		y += dy;

		if (fireball)
		{
			//pool->Create()->Init(mario, this);
			fireball = false;
		}

		//xet nx va huong ban theo x y cua Mario
		float x_mario, y_mario;
		mario->GetPosition(x_mario, y_mario);
		if (x_mario < x)
			nx = -1;
		else	
			nx = 1;

		if (GetTickCount64() - shoot_time_start > PLANT_SHOOT_TIME || shoot == false)
		{
			if (y_mario > y)
				isUp = false;
			else if (y_mario < y)
				isUp = true;
		}

		//xet len xuong bang va cham aabb
		/*for (int i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CGround*>(coObjects->at(i)))
			{	
				if (AABB(coObjects->at(i)) == false)
				{
					vy = -vy;
				}	
			}
		}	*/

		//if (!shoot)
		//{
		//	if (pipe == 0) //ko con aabb voi pipe
		//	{
		//		vy = 0.0f;
		//		StartShootTime();
		//	}
		//}
		//else if (GetTickCount64() - shoot_time_start > PLANT_SHOOT_TIME)
		//{
		//	shoot = false;
		//	vy = PLANT_SPEED;
		//}
	}	
}

void CPlant::Render()
{
	if (die == false)
	{
		int ani = 0;
		if (!shoot)
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
	RenderBoundingBox();
}

void CPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PLANT_WIDTH;
	b = y + PLANT_HEIGHT;
}

