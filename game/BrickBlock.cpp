#include "BrickBlock.h"
#include "Utils.h"

BrickBlock::BrickBlock()
{
	SetAnimation(BRICK_ANI_ID);
}

void BrickBlock::SetAnimation(int ani)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ani);
	SetAnimationSet(ani_set);
}

void BrickBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void BrickBlock::Render()
{
	int ani;
	animation_set->at(0)->Render(x, y, NULL);
}

void BrickBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}