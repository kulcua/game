#pragma once
#include "GameObject.h"
#include "Curtain.h"
#define THREE_ANI_ID 63
class Three : public CGameObject
{
	Curtain* curtain;
public:
	bool isStop = false;
	Three(Curtain* curtain);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
