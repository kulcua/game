#pragma once
#include "Item.h"

#define COIN_BRICK_ANI_ID 25
#define COIN_JUMP_SPEED	0.5f
#define COIN_TIME 700

class CoinBrick : public CItem
{
	int jumpTimeStart;
	void SetAnimation(int ani);
public:
	CoinBrick();
	void StartJump() { jumpTimeStart = GetTickCount64(); }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

