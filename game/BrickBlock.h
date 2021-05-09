#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48
#define BRICK_ANI_ID 23
#define BRICK_ANI_BLOCK 0
#define BRICK_ANI_COIN 1

class BrickBlock : public CGameObject
{
	friend class CMario;
	CMario* mario;
public:
	BrickBlock();
	bool isCoin;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

