#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"

#define ITEM_BBOX_WIDTH  16
#define ITEM_BBOX_HEIGHT 15

#define ITEM_GRAVITY	0.0015f

#define ITEM_STATE_RED_MUSHROOM	26
#define ITEM_RED_MR_VY 0.007f
#define ITEM_RED_MR_VX 0.05f

#define ITEM_STATE_LEAF	27
#define ITEM_LEAF_VX 0.08f
#define ITEM_LEAF_A	0.0001f
#define ITEM_LEAF_DROP_SPEED	0.01f
#define ITEM_LEAF_TIME	50

class CItem :public CGameObject
{
protected:
	CBrick* brick;
public:
	void SetBrick(CBrick* brick) { this->brick = brick; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

