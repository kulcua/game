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

typedef Layer* LPLAYER;

class TileMap
{
	static TileMap* __instance;
	Tileset* tileSet;
	vector<LPLAYER> layers;
	Layer* foreground;
	ObjectMap* objectMap;
public:
	bool ReadFileTmx(const char* pathTmx, int id, D3DCOLOR transColor, vector<LPGAMEOBJECT> &objects, CMario *mario);
	void Render();
	void RenderForeground();
	static TileMap* GetInstance();
};

