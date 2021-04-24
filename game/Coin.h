#pragma once
#include "GameObject.h"
#define COIN_BBOX_WIDTH  48
#define COIN_BBOX_HEIGHT 48
#define COIN_ANI_ID 28

class Coin : public CGameObject
{
	void SetAnimation(int ani);
public:
	Coin();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

