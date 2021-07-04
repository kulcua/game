#pragma once
#include "Utils.h"
#include "tinyxml.h"
#include "GameObject.h"
#define TILE_SIZE 48
class ObjectMap
{
	TiXmlElement* objectGroupElement;
	int objectGroupId;
	string name;
	Grid* grid;
public:
	ObjectMap(TiXmlElement* objectGroupElement, vector<LPGAMEOBJECT> &objects, Grid* grid);
	void ImportData(vector<LPGAMEOBJECT>& objects);
};

template <class T>
void splitToTile(float x, float y, float w, float h, Grid* grid, vector<LPGAMEOBJECT>& objects)
{
	float x_, y_;
	int cell_x = round(w / TILE_SIZE);
	int cell_y = round(h / TILE_SIZE);
	if (cell_x > 0 && cell_y > 0)
	{
		for (int i = 0; i < cell_x; i++)
		{
			for (int j = 0; j < cell_y; j++)
			{
				T* obj = new T();
				x_ = i * TILE_SIZE + x;
				y_ = j * TILE_SIZE + y;
				obj->SetPosition(x_, y_);
				obj->SetGrid(grid);
				objects.push_back(obj);
			}
		}
	}
}
