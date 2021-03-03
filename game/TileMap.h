#pragma once
#include "fstream"
#include "Sprites.h"
#include <string>
#include "Utils.h"
#include "tinyxml.h"
#include "Tileset.h"

class TileMap
{
	static TileMap* __instance;
	Tileset* tileSet;
public:
	bool ReadFileTmx(const char* pathTmx, int id, D3DCOLOR transColor);
	static TileMap* GetInstance();
};

