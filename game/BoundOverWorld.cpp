#include "BoundOverWorld.h"
BoundOverWorld::BoundOverWorld(float w, float h)
{
	width = w;
	height = h;
}

void BoundOverWorld::Render()
{
	//RenderBoundingBox();
}

void BoundOverWorld::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}