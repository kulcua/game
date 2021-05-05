#pragma once
#include "GameObject.h"
class CCameraBound : public CGameObject
{
	int type;
public:
	CCameraBound(float w, float h, int type);
	int GetType() { return type; }
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};