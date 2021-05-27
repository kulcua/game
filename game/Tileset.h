#pragma once
#include "fstream"
#include "Sprites.h"
#include "Utils.h"
#include "tinyxml.h"

class Tileset
{
	//const string prefix = "map/World-map-1-1/";
	string prefixPath;
	TiXmlElement* tileset;
	int textureId;
	D3DCOLOR transColor;

	int tileWidth;
	int tileHeight;
	int tileCount;
	int columns;
	int rows;
	LPCWSTR pathImage;
public:
	Tileset(TiXmlElement* tileset, int id, D3DCOLOR transColor, string prefixPath);
	void SplitImageToTile();
};

