#pragma once
#include "GameObject.h"

#define PIPE_WIDTH 16
#define PIPE_HEIGHT 16

class CPipe : public CGameObject
{
	int width;
	int height;
	int spriteId;
public:
	CPipe(float x, float y, int spriteId);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

