#include "Ground.h"
#include "Animations.h"
#include "Utils.h"

CGround::CGround(float l, float t, float w, float h)
{
	x = l;
	y = t;
	width = w;
	height = h;
}

void CGround::Render()
{
	//RenderBoundingBox();
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

