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

	if (jumpTimeStart == 0)
	{
		StartJump();
		vy = -COIN_JUMP_SPEED;
	}
	else if (GetTickCount64() - jumpTimeStart > COIN_TIME)
	{
		jumpTimeStart = 0;
		die = true;
	}
	else
	{
		vy += ITEM_GRAVITY * dt;
		y += dy;
	}
}

void Coin::Render()
{
	CItem::Render();
}