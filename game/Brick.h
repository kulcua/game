#pragma once
#include "GameObject.h"
#include "Item.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_ENABLE 100
#define BRICK_STATE_DISABLE	200

#define BRICK_ANI_ENABLE	0
#define BRICK_ANI_DISABLE	1

#define BRICK_JUMP_DEFLECT_Y 8.0f

class CBrick: public CGameObject
{
	float start_y;
public:
	CBrick(float y);
	void SetState(int state);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};