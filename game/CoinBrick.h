#pragma once
#include "Item.h"

#define COIN_BRICK_ANI_ID 25
#define COIN_JUMP_SPEED	0.5f
#define COIN_TIME 900

class CoinBrick : public CItem
{
	int jumpTimeStart;
public:
	CoinBrick();
	void StartJump() { jumpTimeStart = GetTickCount64(); }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

