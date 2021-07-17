#pragma once
#include "GameObject.h"
class CGround : public CGameObject
{
public:
	CGround(float w, float h);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
