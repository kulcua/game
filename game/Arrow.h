#pragma once
#include "GameObject.h"
#include "Curtain.h"
#define ARROW_ANI_ID 65
class Arrow : public CGameObject
{
public:
	Arrow();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
