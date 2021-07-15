#pragma once
#include "GameObject.h"
class CCameraBound : public CGameObject
{
	int type;
public:
	CCameraBound(int type, float w, float h);
	int GetType() { return type; }
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};