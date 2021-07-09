#include "Ground.h"
#include "Utils.h"

void CGround::Render()
{
	//RenderBoundingBox();
}

//CGround::CGround(float w, float h)
//{
//	this->width = w;
//	this->height = h;
//}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + GROUND_SIZE;
	b = y + GROUND_SIZE;
}

