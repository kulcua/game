#pragma once
#include "Item.h"
#define GREEN_MUSHROOM_ANI_ID 29

class GreenMushroom : public CItem
{
	bool outBrick;
	float startY;
public:
	GreenMushroom(float y);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
