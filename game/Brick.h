#pragma once
#include "GameObject.h"
#include "Item.h"

#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48

#define BRICK_STATE_ENABLE 100
#define BRICK_STATE_DISABLE	200

#define BRICK_ANI_ENABLE	0
#define BRICK_ANI_DISABLE	1

#define BRICK_JUMP_DEFLECT_Y 0.8f
#define BRICK_ANI_ID 22

class CBrick: public CGameObject
{
	float start_y;
	//int typeItem;
	string name;
	void SetAnimation(int ani);
public:
	bool dropItem = false;
	CBrick(float x, float y, string name);
	void SetState(int state);
	//int GetTypeItem() { return typeItem; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};