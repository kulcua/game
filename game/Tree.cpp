#include "Tree.h"
#define TREE_ANI_ID	3
Tree::Tree()
{
	SetAnimation(TREE_ANI_ID);
}

void Tree::Render()
{
	animation_set->at(0)->Render(x, y, nx, ny, 255);
	//RenderBoundingBox();
}

void Tree::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + TREE_WIDTH;
	b = y + TREE_HEIGHT;
}