#pragma once
#include "GameObject.h"
class BoundOverWorld : public CGameObject
{
public:
	BoundOverWorld(float w, float h);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};