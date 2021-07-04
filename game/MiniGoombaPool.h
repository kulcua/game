#pragma once
#include "MiniGoomba.h"
#include "Grid.h"

class MiniGoombaPool
{
	static MiniGoombaPool* __instance;
	static const int POOL_SIZE = 4;
	MiniGoomba* miniGoomba[POOL_SIZE];
	MiniGoomba* firstAvailable_;
	Grid* grid;
public:
	static MiniGoombaPool* GetInstance();
	void InitPool(vector<LPGAMEOBJECT>& objects);
	MiniGoomba* Create();
	void GetBackToPool();
	void SetGrid(Grid* grid) { this->grid = grid; }
	int CheckNumberInPool();
};
