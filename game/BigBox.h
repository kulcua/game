#pragma once
#include "GameObject.h"
class CBigBox :public CGameObject
{
public:
	CBigBox(float w, float h);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
