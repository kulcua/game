#pragma once
#include "GameObject.h"
class CGround : public CGameObject
{
public:
	CGround(float l, float t, float w, float h);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

