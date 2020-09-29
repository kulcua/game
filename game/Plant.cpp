#include "Plant.h"
#include "Ground.h"
#include "Utils.h"
#include "Pipe.h"

CPlant::CPlant() {
	SetState(PLANT_STATE_ENABLE);
	die = false;
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!die)
	{
		CGameObject::Update(dt, coObjects);
		y += dy;
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
				}
			}	
		}	
		if (pipe == 0)
		{
			vy = -vy;
		}	
	}	
}

void CPlant::Render()
{
	int ani;
	if (state == PLANT_STATE_ENABLE)
	{
		ani = PLANT_ANI_DOWN;
	}
	animation_set->at(ani)->Render(x, y, NULL);
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

