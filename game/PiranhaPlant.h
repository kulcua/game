#pragma once
#include "Plant.h"

class PiranhaPlant : public CPlant
{
public:
	PiranhaPlant(float y) : CPlant(y) {};
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

