#pragma once
#include "GameObject.h"
#include "Mario.h"

class CCamera : public CGameObject
{
	CMario* mario;

	float xCenter;
	float yCenter;
	
	bool onGroundMode;

	bool isMove;
public:
	CCamera();
	void FollowMario();
	void SetPosition(float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_object);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetIsMove(bool isMove) { this->isMove = isMove; }
};

