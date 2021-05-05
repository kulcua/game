#include "CameraBound.h"
#include "Utils.h"

CCameraBound::CCameraBound(float w, float h, int type)
{
	width = w;
	height = h;
	this->type = type;
	nx = NULL;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(0);
	SetAnimationSet(ani_set);
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