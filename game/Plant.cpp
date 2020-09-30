#include "Plant.h"
#include "Ground.h"
#include "Pipe.h"
#include "Mario.h"
#include "PlayScene.h"

CPlant::CPlant(CGameObject *player) {
	SetState(PLANT_STATE_ENABLE);
	die = false;
	shoot = false;
	nx = -1;
	this->player = player;
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!die)
	{
		CGameObject::Update(dt, coObjects);
		
		//xet nx va huong ban theo x y cua Mario
		float x_mario, y_mario;
		player->GetPosition(x_mario, y_mario);
		if (x_mario < x)
			nx = -1;
		else	
			nx = 1;

		if (GetTickCount() - shoot_time_start > PLANT_SHOOT_TIME || !shoot)
		{
			if (y_mario > y)
				isUp = false;
			else if (y_mario < y)
				isUp = true;
		}
		
		y += dy;// di chuyen theo y bt

		//xet len xuong bang va cham aabb
		int pipe = 0;
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CPipe*>(coObjects->at(i)))
			{	
				if (AABB(coObjects->at(i)))
				{
					pipe++;
				}	
			}
			if (dynamic_cast<CGround*>(coObjects->at(i)))
			{
				if (AABB(coObjects->at(i)))
				{
					vy = -vy;
					break;
				}
			}	
		}	

		if (!shoot)
		{
			if (pipe == 0)
			{
				vy = 0.0f;
				StartShootTime();
			}
		}
		else if (GetTickCount() - shoot_time_start > PLANT_SHOOT_TIME)
		{
			shoot = false;
			vy = PLANT_SPEED;
		}
	}	
}

void CPlant::Render()
{
	int ani;
	if (state == PLANT_STATE_ENABLE)
	{
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
	}
	animation_set->at(ani)->Render(x, y, nx);
	//RenderBoundingBox();
}

void CPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLANT_STATE_ENABLE:
		vy = -PLANT_SPEED;
	default:
		break;
	}
}

void CPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PLANT_WIDTH;
	b = y + PLANT_HEIGHT;
}

