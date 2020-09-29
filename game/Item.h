#pragma once
#include "GameObject.h"

#define ITEM_BBOX_WIDTH  16
#define ITEM_BBOX_HEIGHT 20

#define ITEM_STATE_DISABLE 0
#define ITEM_STATE_ENABLE	1

#define ITEM_GRAVITY	0.002f

#define ITEM_COIN_JUMP_SPEED	1.0f

enum ItemType {
	COIN,
	RED_MUSH,
	LEAF,
	//switchbox,
	//green_mushroom
};

class CItem :public CGameObject
{
	//ItemType type;
public:
	CItem();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

