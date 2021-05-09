#pragma once
#include "GameObject.h"
#include "Item.h"

#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48

#define BRICK_STATE_ENABLE 100
#define BRICK_STATE_DISABLE	200
#define BRICK_JUMP_DEFLECT_Y 0.8f
#define BRICK_RETURN_START_POS_VY 0.05f
#define BRICK_ANI_ID 22
#define BRICK_ANI_QUESTION 0
#define BRICK_ANI_BLOCK 1
#define BRICK_ANI_DISABLE	2

#define BRICK_TYPE_QUESTION	1
#define BRICK_TYPE_BLOCK	2

class CBrick: public CGameObject
{
	CItem* item;
	int type;
public:
	float start_y;
	CBrick(int type, float x, float y);

	int GetType() { return type; }
	void SetItem(CItem* item) { this->item = item; }
	void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};