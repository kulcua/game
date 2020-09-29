#pragma once
#include "GameObject.h"
#define PLANT_STATE_DISABLE 100
#define PLANT_STATE_ENABLE 200

#define PLANT_ANI_DOWN 0
#define PLANT_ANI_UP 1
#define PLANT_ANI_SHOOT_DOWN 2
#define PLANT_ANI_SHOOT_UP 3

#define PLANT_WIDTH 16
#define PLANT_HEIGHT 32
#define PLANT_SPEED 0.02f

class CPlant : public CGameObject
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	CPlant();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

