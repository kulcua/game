#pragma once
#include "GameObject.h"
class CCameraBound : public CGameObject
{
public:
	CCameraBound(float l, float t, float w, float h);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};