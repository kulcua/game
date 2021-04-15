#include "BigBox.h"

CBigBox::CBigBox(float w, float h)
{
	width = w;
	height = h;
}

void CBigBox::Render()
{
	//RenderBoundingBox();
}

void CBigBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}