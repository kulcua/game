#include "Cell.h"

void Cell::AddObject(CGameObject* obj)
{
	if (objects.find(obj) == objects.end())
	{
		objects.insert(obj);
	}
}

void Cell::RemoveObject(CGameObject* obj)
{
	if (objects.find(obj) != objects.end())
	{
		objects.erase(obj);
	}
}

void Cell::Update(DWORD dt, vector<LPGAMEOBJECT> coObjects)
{
	vector<CGameObject*> objList = GetListObjects();
	for (size_t i = 0; i < objList.size(); i++)
	{
		objList[i]->Update(dt, &coObjects);
	}
}

void Cell::Render()
{
	vector<CGameObject*> objList = GetListObjects();
	for (size_t i = 0; i < objList.size(); i++)
	{
		objList[i]->Render();
	}
}

vector<LPGAMEOBJECT> Cell::GetListObjects()
{
	vector<CGameObject*> activeObjects;
	for (auto o : objects)
	{
		if (o->die == false)
			activeObjects.push_back(o);
	}
	return activeObjects;
}
