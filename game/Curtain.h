#pragma once
#include "GameObject.h"
#define CURTAIN_ANI_ID 60
#define CURTAIN_ANI_RED 0
#define CURTAIN_ANI_BROS 1
class Curtain : public CGameObject
{
public:
	int ani;
	Curtain();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
