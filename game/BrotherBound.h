#pragma once
#include "GameObject.h"
class BrotherBound : public CGameObject
{
public:
	BrotherBound(float w, float h);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};