#pragma once
#include "Enermy.h"
#include "Utils.h"

#define PLANT_STATE_DIE 100
#define PLANT_SPEED 0.04f
#define PLANT_WIDTH 50
#define PLANT_HEIGHT 94
#define PLANT_NEAR_MARIO_DISTANCE 100

class CPlant : public Enermy
{
protected:
	float startY;
	bool isNearMario;
public:
	CPlant(float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

