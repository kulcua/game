#include "Ground.h"
#include "Utils.h"

CGround::CGround(float w, float h)
{
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

