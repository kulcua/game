#include "DialogOverWorld.h"

DialogOverWorld::DialogOverWorld()
{
	this->width = DIALOG_WIDTH;
	this->height = DIALOG_HEIGHT;
	SetAnimation(DIALOG_ANI_ID);
}

void DialogOverWorld::Render()
{
	animation_set->at(0)->Render(x, y, nx, ny);
	//RenderBoundingBox();
}

void DialogOverWorld::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}