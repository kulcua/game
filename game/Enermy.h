#pragma once
#include "GameObject.h"
#include "Mario.h"
#define ENERMY_DEFECT_VY_KICKED 0.5f
#define ENERMY_DIE_TIME 1000
class Enermy : public CGameObject
{
protected:
	CMario* mario;
	DWORD dieTimeStart;
	bool isOnGround;
public:
	void BeingKicked();
	void StartDieTime() { dieTimeStart = GetTickCount64(); }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void Render() = 0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
};

