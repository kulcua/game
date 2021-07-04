#pragma once
#include "GameObject.h"
#define TREE_WIDTH 45
#define TREE_HEIGHT 45

class Tree :public CGameObject
{
public:
	Tree();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

