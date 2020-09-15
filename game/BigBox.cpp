#include "BigBox.h"

CBigBox::CBigBox(float l, float t, float r, float b)
{
	x = l;
	y = t;
	width = r - l + 1;
	height = b - t + 1;
	nx = NULL; //gan bang null cho khoi chay lung tung
	left = l;
	right = r;
}

void CBigBox::Render()
{
	RenderBoundingBox();
}

void CBigBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}