#pragma once
#include "GameObject.h"
class Enermy : public CGameObject
{
public:
	virtual Enermy* Clone() = 0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};