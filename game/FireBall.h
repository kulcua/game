#pragma once
#include "GameObject.h"
#define FIREBALL_WIDTH 9
#define FIREBALL_HEIGHT 9
#define FIREBALL_SPEED 0.2f
#define FIREBAL_ANI_ID 62

class CFireBall : public CGameObject
{
public:
	CFireBall(CGameObject *plant);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};