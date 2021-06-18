#pragma once
#include "Utils.h"
#define NUM_CELLS 30
#define CELL_SIZE_X 400
#define CELL_SIZE_Y 300
class Grid
{
	friend class CGameObject;
	CGameObject* cells_[NUM_CELLS][NUM_CELLS];
public:
	Grid();
	void Add(CGameObject* obj);
	void Update(DWORD dt);
	void Render();
	void GetCell(int& startX, int& startY, int& endX, int& endY);
	void Move(CGameObject* obj, int x, int y);
};

