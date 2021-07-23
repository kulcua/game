#pragma once
#include "GameObject.h"
#include "Item.h"

#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48
#define BRICK_STATE_DISABLE	500
#define BRICK_JUMP_DEFLECT_Y 0.3f
#define BRICK_RETURN_START_POS_VY 0.1f
#define BRICK_ANI_ID 22
#define BRICK_ANI_QUESTION 0
#define BRICK_ANI_BLOCK 1
#define BRICK_ANI_DISABLE	2
#define BRICK_TYPE_QUESTION	1
#define BRICK_TYPE_BLOCK	2
#define BRICK_LEVEL_1_ITEM	1
#define BRICK_LEVEL_MANY_ITEM	2

class CBrick: public CGameObject
{
	CItem* item;
protected:
	int type;
	int level;
public:
	float start_y;
	CBrick(int type, float x, float y);
	int GetType() { return type; }
	void SetItem(CItem* item) { this->item = item; }
	int GetLevel() { return level; }
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};