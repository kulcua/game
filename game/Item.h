#pragma once
#include "GameObject.h"

#define ITEM_BBOX_WIDTH  16
#define ITEM_BBOX_HEIGHT 16

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
	ItemType type;
public:
	CItem(ItemType type) { this->type = type; };
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

