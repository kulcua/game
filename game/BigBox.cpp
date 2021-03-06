#include "BigBox.h"

CBigBox::CBigBox(float l, float t, float w, float h)
{
	x = l;
	y = t;
	width = w;
	height = h;
	nx = NULL; //gan bang null cho khoi chay lung tung
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