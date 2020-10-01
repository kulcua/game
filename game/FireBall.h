#pragma once
#include "GameObject.h"
#include "Plant.h"
#include "Mario.h"

#define FIREBALL_WIDTH 9
#define FIREBALL_HEIGHT 9
#define FIREBALL_SPEED 0.06f
#define FIREBAL_ANI_ID 62
#define FIREBALL_CHECK_X 72
#define FIREBALL_CHECK_Y 150

class CFireBall : public CGameObject
{
	CMario* player;
	CPlant* plant;
public:
	CFireBall(CMario *player, CPlant*plant);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};