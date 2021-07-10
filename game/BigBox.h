#pragma once
#include "GameObject.h"
class CBigBox :public CGameObject
{
	int type;
public:
	CBigBox(float w, float h);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetType(int type) { this->type = type; }
	int GetType() { return type; }
};
