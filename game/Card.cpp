#include "Card.h"

Card::Card()
{
	SetAnimation(CARD_ANI_ID);
}

void Card::SetAnimation(int ani)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ani);
	SetAnimationSet(ani_set);
}

void Card::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void Card::Render()
{
	animation_set->at(0)->Render(x, y, nx);
}

void Card::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CARD_BBOX_WIDTH;
	b = y + CARD_BBOX_HEIGHT;
}