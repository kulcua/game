#include "CoinBrick.h"
#include "EffectPool.h"
#include "Mario.h"

CoinBrick::CoinBrick()
{
	SetAnimation(COIN_BRICK_ANI_ID);
}

void CoinBrick::SetAnimation(int ani)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ani);
	SetAnimationSet(ani_set);
}

void CoinBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
		CMario::GetInstance()->SetMoney(1);
		Effect* effect = EffectPool::GetInstance()->Create();
		if (effect != NULL)
			effect->InitPoint(EffectPoint::p100, x, y);
	}
	else
	{
		vy += ITEM_GRAVITY * dt;
		y += dy;
	}
}

void CoinBrick::Render()
{
	CItem::Render();
}