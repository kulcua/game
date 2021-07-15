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

	if (jumpTimeStart == 0)
	{
		StartJump();
		vy = -COIN_JUMP_SPEED;
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
			vy += ITEM_GRAVITY * dt;
			y += dy;
		}
	}
}

void CoinBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 0;
	b = y + 0;
}

void CoinBrick::Render()
{
	CItem::Render();
}