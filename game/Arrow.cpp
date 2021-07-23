#include "Arrow.h"
#include "Utils.h"

Arrow::Arrow()
{
	SetAnimation(ARROW_ANI_ID);
	die = true;
}

void Arrow::Render()
{
	animation_set->at(0)->Render(x, y, nx, ny);
	//RenderBoundingBox();
}

void Arrow::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x;
	b = y;
}
