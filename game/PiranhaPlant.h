#pragma once
#include "Plant.h"

#define PIRANHA_WIDTH 50
#define PIRANHA_HEIGHT 70

class PiranhaPlant : public CPlant
{
public:
	PiranhaPlant(float y) : CPlant(y) {};
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

