#pragma once
#include "Item.h"

#define COIN_BRICK_ANI_ID 25
#define COIN_JUMP_SPEED	0.7f
#define COIN_DROP_SPEED	0.02f
#define COIN_TIME 500

class CoinBrick : public CItem
{
	ULONGLONG jumpTimeStart;
public:
	CoinBrick();
	void StartJump() { jumpTimeStart = GetTickCount64(); }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

