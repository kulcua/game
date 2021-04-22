#pragma once
#include "GameObject.h"
#include "Utils.h"

#define ITEM_BBOX_WIDTH  48
#define ITEM_BBOX_HEIGHT 48

#define ITEM_GRAVITY	0.001f

#define ITEM_STATE_RED_MUSHROOM	26
#define ITEM_RED_MR_VY 0.03f
#define ITEM_RED_MR_VX 0.1f

#define ITEM_STATE_LEAF	27
#define LEAF_DEFLECT_SPEED 0.7f
#define ITEM_LEAF_VX 0.5f
#define ITEM_LEAF_A	0.0001f
#define ITEM_LEAF_DROP_SPEED	0.03f
#define ITEM_LEAF_TIME	50

class CItem :public CGameObject
{
protected:
public:
	CItem();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

