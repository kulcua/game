#include "Coin.h"

Coin::Coin()
{
	SetAnimation(COIN_ANI_ID);
}

void Coin::SetAnimation(int ani)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ani);
	SetAnimationSet(ani_set);
}

void Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void Coin::Render()
{
	animation_set->at(0)->Render(x, y, nx);
}

void Coin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COIN_BBOX_WIDTH;
	b = y + COIN_BBOX_HEIGHT;
}