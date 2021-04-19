#include "PowerUpItem.h"
#include "Animations.h"
#include "Mario.h"

PowerUpItem::PowerUpItem()
{
	SetAnimation(0);
}

void PowerUpItem::SetAnimation(int ani)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(0);
	SetAnimationSet(ani_set);

	mario = CMario::GetInstance();
}

void PowerUpItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (brick->dropItem)
	{
		brick->dropItem = false;

		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
			SetAnimation(RED_MUSHROOM_ANI_ID);
		else
			SetAnimation(LEAF_ANI_ID);
	}
}

void PowerUpItem::Render()
{
	CItem::Render();
}
