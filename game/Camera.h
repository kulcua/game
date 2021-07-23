#pragma once
#include "GameObject.h"
#include "Mario.h"
#define CAM_WIDTH 800
#define CAM_HEIGHT 600
#define CAM_INIT_BOUND 20
#define CAM_VY_SCROLL 0.08f
class CCamera : public CGameObject
{
	CMario* mario;

	float xCenter;
	float yCenter;

	float startX, startY;
	bool isMove;
public:
	bool isScroll;
	CCamera();
	void FollowMario();
	void SetPosition(float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_object);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetIsMove(bool isMove) { this->isMove = isMove; }
	void ResetPosition();
	void ScrollMode();
};

