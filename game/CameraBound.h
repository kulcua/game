#pragma once
#include "GameObject.h"
#define CAM_BOUND_SIZE 48
class CCameraBound : public CGameObject
{
	int type;
public:
	CCameraBound(int type);
	int GetType() { return type; }
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};