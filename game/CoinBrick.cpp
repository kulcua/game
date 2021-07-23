#include "CoinBrick.h"
#include "EffectPool.h"
#include "Mario.h"
#include "Game.h"

CoinBrick::CoinBrick()
{
	SetAnimation(COIN_BRICK_ANI_ID);
	jumpTimeStart = 0;
}

void CoinBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	y += dy;

	if (jumpTimeStart == 0)
	{
		vy = -COIN_JUMP_SPEED;
		StartJump();
	}
	else
	{
		if (GetTickCount64() - jumpTimeStart > COIN_TIME)
		{
			jumpTimeStart = 0;
			die = true;
			CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetMoney(1);
			Effect* effect = EffectPool::GetInstance()->Create();
			if (effect != NULL)
				effect->InitPoint(EffectPoint::p100, x, y);
		}
		else
		{
			vy += COIN_DROP_SPEED;	
		}
	}
}

void CoinBrick::Render()
{
	CItem::Render();
}