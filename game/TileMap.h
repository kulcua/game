#pragma once
#include "fstream"
#include "Sprites.h"
#include "Utils.h"
#include "tinyxml.h"
#include "Tileset.h"
#include "Layer.h"

class TileMap
{
	static TileMap* __instance;
	Tileset* tileSet;
	Layer* layer;
public:
	bool ReadFileTmx(const char* pathTmx, int id, D3DCOLOR transColor);
	static TileMap* GetInstance();
};

