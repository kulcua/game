#pragma once
#include "GameObject.h"
#define CURTAIN_ANI_ID 60
class Curtain : public CGameObject
{
public:
	Curtain();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
