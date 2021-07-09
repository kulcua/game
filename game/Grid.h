#pragma once
#include "Utils.h"
#include <unordered_map>
#define NUM_CELLS 40
#define CELL_SIZE 400

class Grid
{
	friend class CGameObject;
	CGameObject* cells_[NUM_CELLS][NUM_CELLS];
	// object_id - cell number x y
	unordered_map<int, D3DXVECTOR2> objectCells;
public:
	Grid();
	void Add(CGameObject* obj);
	void Add(CGameObject* obj, int id);
	void Update(DWORD dt);
	void Render();
	void GetCell(int& startX, int& startY, int& endX, int& endY);
	void Move(CGameObject* obj, float x, float y);
	void ReadGridData(const char* filePath);
};

