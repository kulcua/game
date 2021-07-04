#pragma once
#include "Boomerang.h"
#include "Grid.h"

class BoomerangPool
{
	static BoomerangPool* __instance;
	static const int POOL_SIZE = 2;
	Boomerang* boomerang[POOL_SIZE];
	Boomerang* firstAvailable_;
	Grid* grid;
public:
	static BoomerangPool* GetInstance();
	void InitPool(vector<LPGAMEOBJECT>& objects);
	Boomerang* Create();
	void GetBackToPool();
	void SetGrid(Grid* grid) { this->grid = grid; }
	bool CheckBoomerangInPool(int index);
};

