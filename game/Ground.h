#pragma once
#include "GameObject.h"
#define GROUND_SIZE 48
class CGround : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

