#include "CameraBound.h"
#include "Utils.h"

CCameraBound::CCameraBound(int type)
{
	this->type = type;
}

void CCameraBound::Render()
{
	//RenderBoundingBox();
}

void CCameraBound::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CAM_BOUND_SIZE;
	b = y + CAM_BOUND_SIZE;
}