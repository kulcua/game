#include "Plant.h"
#include "Ground.h"
#include "Pipe.h"
#include "Mario.h"
#include "PlayScene.h"

CPlant::CPlant() {
	SetState(PLANT_STATE_ENABLE);
	die = false;
	shoot = false;
	nx = -1;
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!die)
	{
		DebugOut(L"time: %d tick: %d vy: %f\n", shoot_time_start, GetTickCount(), vy);
		CGameObject::Update(dt, coObjects);
		
		//xet nx theo xMario
		//float x_mario, y_mario;
		//CMario::GetInstance()->GetPosition(x_mario, y_mario);
		/*CMario * mario = ((CPlayScene*)scene)->GetPlayer();
		DebugOut(L"mario: %f\n", x_mario);
		if (x_mario < x)
		{
			nx = -1;
		}
		else
		{
			nx = 1;
			DebugOut(L"right mario: %f\n", x_mario);
		}	*/

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
			ani = PLANT_ANI_DOWN;
		else ani = PLANT_ANI_SHOOT_DOWN;
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

