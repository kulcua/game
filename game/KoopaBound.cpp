#include "KoopaBound.h"
#include "Utils.h"

KoopaBound::KoopaBound(float w, float h)
{
	width = w;
	height = h;
	nx = NULL;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(0);
	SetAnimationSet(ani_set);
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