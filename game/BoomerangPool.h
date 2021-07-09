#pragma once
#include "Boomerang.h"
#include "Grid.h"

class BoomerangPool
{
	static BoomerangPool* __instance;
	static const int POOL_SIZE = 2;
	Boomerang* boomerang[POOL_SIZE];
	Boomerang* firstAvailable_;
public:
	static BoomerangPool* GetInstance();
	void InitPool(vector<LPGAMEOBJECT>& objects);
	Boomerang* Create();
	void GetBackToPool();
	bool CheckBoomerangInPool(int index);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

