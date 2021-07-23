#include "CameraBound.h"
#include "Utils.h"

CCameraBound::CCameraBound(float w, float h)
{
	this->width = w;
	this->height = h;
}

void CCameraBound::Render()
{
	//RenderBoundingBox();
}

void CCameraBound::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}