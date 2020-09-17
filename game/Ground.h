#pragma once
#include "GameObject.h"
class CGround : public CGameObject
{
	int width;
	int height;
public:
	//int GetHeight() { return height; }
	CGround(float l, float t, float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

