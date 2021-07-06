#pragma once
#include "GameObject.h"
class Enermy : public CGameObject
{
protected:
	friend class CMario;
	CMario* mario;
	DWORD dieTimeStart;
	bool isOnGround;
public:
	void StartDieTime() { dieTimeStart = GetTickCount64(); }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void Render() = 0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
};

