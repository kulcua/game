#pragma once
#include "GameObject.h"
class KoopaBound : public CGameObject
{
public:
	KoopaBound(float w, float h);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};