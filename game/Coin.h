#pragma once
#include "Item.h"

#define COIN_ANI_ID 25
#define COIN_JUMP_SPEED	0.5f
#define COIN_TIME 700

class Coin : public CItem
{
	int jumpTimeStart;
public:
	Coin();
	void SetAnimation(int ani);
	void StartJump() { jumpTimeStart = GetTickCount64(); }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

