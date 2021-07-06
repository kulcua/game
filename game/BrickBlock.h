#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48
#define BRICKBLOCK_ANI_ID 23
#define BRICK_ANI_BRICKBLOCK 0
#define BRICK_ANI_COIN 1
#define BRICK_BLOCK_TIME_COIN_DISAPPEAR 4000

class BrickBlock : public CGameObject
{
	friend class CMario;
	CMario* mario;
	int coinTimeStart = 0;
public:
	BrickBlock();
	bool isCoin;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void StartToCoin() { coinTimeStart = GetTickCount64(); isCoin = true; }
};

