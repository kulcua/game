#pragma once
#include "GameObject.h"
#include <unordered_set>
class Cell
{
	unordered_set<LPGAMEOBJECT> objects;
public:
	void AddObject(CGameObject* obj);
	void RemoveObject(CGameObject* obj);
	void Update(DWORD dt, vector<LPGAMEOBJECT> coObjects);
	void Render();
	vector<LPGAMEOBJECT> GetListObjects();
};

