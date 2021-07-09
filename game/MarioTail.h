#pragma once
#include "GameObject.h"
class MarioTail : public CGameObject
{
	friend class CMario;
	CMario* mario;
public:
	MarioTail();
	void HandleCollision(vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};


