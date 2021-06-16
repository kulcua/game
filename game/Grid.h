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
	//void HandleMelee();
	//void HandleCell(int x, int y);
	void Move(CGameObject* obj, double x, double y);
	//void HandleObject(CGameObject* obj, CGameObject* other);
};

