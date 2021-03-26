#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Game.h"

class CCamera : public CGameObject
{
	CMario* mario;
	CGame* game;

	float xCenter;
	float yCenter;
public:
	CCamera(CMario* mario, float x, float y, float width, float height);
	void FollowMario();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_object);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
