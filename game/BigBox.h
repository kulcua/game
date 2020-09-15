#pragma once
#include "GameObject.h"
class CBigBox :public CGameObject
{ 
	int width;
	int height;

public:
	int left; int right;
	CBigBox(float l, float t, float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

