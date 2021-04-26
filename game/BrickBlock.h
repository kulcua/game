#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48
#define BRICK_ANI_ID 23

class BrickBlock : public CGameObject
{
	void SetAnimation(int ani);
public:
	BrickBlock();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

