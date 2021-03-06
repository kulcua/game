#include "Ground.h"
#include "Animations.h"
#include "Utils.h"

CGround::CGround(float l, float t, float w, float h)
{
	x = l;
	y = t;
	width = w;
	height = h;
	nx = NULL; //gan bang null cho khoi chay lung tung
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(0);
	SetAnimationSet(ani_set);
}

void CGround::Render()
{
	//RenderBoundingBox();
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

