#pragma once
#include "GameObject.h"
#include "Item.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_ALIVE 100
#define BRICK_STATE_DIE	200

#define BRICK_ANI_ALIVE	0
#define BRICK_ANI_DIE	1

#define BRICK_JUMP_DEFLECT_Y 8.0f

class CBrick: public CGameObject
{
	ItemType type;
	float start_y;
public:
	CBrick(ItemType type, float y);
	ItemType GetItemType() { return type; }
	//turn off update when die
	void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

