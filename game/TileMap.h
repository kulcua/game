#pragma once
#include "fstream"
#include "Sprites.h"
#include "Utils.h"
#include "tinyxml.h"
#include "Tileset.h"
#include "Layer.h"

typedef Layer* LPLAYER;

class TileMap
{
	static TileMap* __instance;
	Tileset* tileSet;
	vector<LPLAYER> layers;
public:
	bool ReadFileTmx(const char* pathTmx, int id, D3DCOLOR transColor);
	void Render();
	static TileMap* GetInstance();
};

