#include "BrickBlock.h"
#include "Utils.h"
#include "Mario.h"

BrickBlock::BrickBlock()
{
	SetAnimation(BRICK_ANI_ID);
	mario = CMario::GetInstance();
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
	if (mario->switchItem)
	{
		isCoin = true;
	}
}

void BrickBlock::Render()
{
	int ani;
	if (isCoin)
		ani = BRICK_ANI_COIN;
	else ani = BRICK_ANI_BLOCK;
	animation_set->at(ani)->Render(x, y, NULL);
}

void BrickBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}