#pragma once
#include "GameObject.h"
#include "Mario.h"

#define ITEM_BBOX_WIDTH  16
#define ITEM_BBOX_HEIGHT 15

#define ITEM_GRAVITY	0.002f

#define ITEM_COIN_JUMP_SPEED	0.5f
#define ITEM_STATE_COIN	25
#define ITEM_COIN_TIME 400

#define ITEM_STATE_RED_MUSHROOM	26 //level 1 of item
#define ITEM_RED_MR_VY 0.007f
#define ITEM_RED_MR_VX 0.05f

#define ITEM_STATE_LEAF	27
#define ITEM_LEAF_VX 0.08f
#define ITEM_LEAF_A	0.001f
#define ITEM_LEAF_DROP_SPEED	0.01f
#define ITEM_LEAF_TIME	50

class CItem :public CGameObject
{
	int type;
	CMario* mario;
	bool isGravity;
	//coin
	bool isFlying = false;
	DWORD fly_time_start;
	void StartFlying();

	bool outBrick = false;

public:
	bool isEnable;
	CItem(int type, CMario *mario);
	void SetState(int state);
	void CollisionAABB(vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

