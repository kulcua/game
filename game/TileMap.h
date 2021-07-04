#pragma once
#include "fstream"
#include "Sprites.h"
#include "Utils.h"
#include "tinyxml.h"
#include "Tileset.h"
#include "Layer.h"
#include "ObjectMap.h"
#include "GameObject.h"
#include "Mario.h"
#include "Grid.h"

typedef Layer* LPLAYER;

class TileMap
{
	static TileMap* __instance;
	Tileset* tileSet;
	vector<LPLAYER> layers;
	Layer* foregroundLayer;
	ObjectMap* objectMap;
	Grid* grid;
public:
	void ReadFileTmx(const char* pathTmx, int id, D3DCOLOR transColor, vector<LPGAMEOBJECT> &objects, string prefixPath);
	void RenderBackground();
	void RenderForeground();
	static TileMap* GetInstance();
	ObjectMap* GetObjectMap() { return objectMap; }
	void Clear();
	void SetGrid(Grid* grid) { this->grid = grid; }
};

