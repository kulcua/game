#include "BrotherBound.h"
#include "Utils.h"

BrotherBound::BrotherBound(float w, float h)
{
	width = w;
	height = h;
}

void BrotherBound::Render()
{
	//RenderBoundingBox();
}

void BrotherBound::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}