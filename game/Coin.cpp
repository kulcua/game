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

	if (brick->dropItem)
	{
		brick->dropItem = false;
		StartJump();
		vy = -COIN_JUMP_SPEED;
	}

	if (GetTickCount64() - jumpTimeStart > COIN_TIME && jumpTimeStart > 0)
	{
		jumpTimeStart = 0;
		die = true;
	}
	else if (jumpTimeStart > 0)
	{
		vy += ITEM_GRAVITY * dt;
		y += dy;
	}	
}

void Coin::Render()
{
	if (jumpTimeStart > 0)
	{
		CItem::Render();
	}
}