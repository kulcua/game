#include "KoopaBound.h"
#include "Utils.h"

KoopaBound::KoopaBound(float w, float h)
{
	width = w;
	height = h;
}

void KoopaBound::Render()
{
	//RenderBoundingBox();
}

void KoopaBound::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}