#include "PiranhaPlant.h"

void PiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (die == false)
	{
		CPlant::Update(dt, coObjects);

		if (y < startY - PIRANHA_HEIGHT && vy < 0) // have not overlap with pipe
		{
			vy = -vy;
		}
	}
}

void PiranhaPlant::Render()
{
	if (die == false)
	{
		animation_set->at(0)->Render(x, y, nx);
	}
	//RenderBoundingBox();
}

void PiranhaPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PIRANHA_WIDTH;
	b = y + PIRANHA_HEIGHT;
}
