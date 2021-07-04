#include "BoundOverWorld.h"

void BoundOverWorld::Render()
{
	//RenderBoundingBox();
}

void BoundOverWorld::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BOUND_SIZE;
	b = y + BOUND_SIZE;
}