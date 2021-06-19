#include "Ground.h"
#include "Utils.h"

void CGround::Render()
{
	//RenderBoundingBox();
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + GROUND_SIZE;
	b = y + GROUND_SIZE;
}

