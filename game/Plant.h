#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Mario.h"

#define PLANT_STATE_DIE 100
#define PLANT_SPEED 0.04f
#define PLANT_WIDTH 50
#define PLANT_HEIGHT 94

class CPlant : public CGameObject
{
protected:
	CMario* mario;
	float startY;
public:
	CPlant(float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

