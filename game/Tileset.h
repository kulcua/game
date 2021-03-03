#pragma once
#include "fstream"
#include "Sprites.h"
#include <string>
#include "Utils.h"
#include "tinyxml.h"

class Tileset
{
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
	Tileset(TiXmlElement* tileset, int id, D3DCOLOR transColor);
	void SplitImageToTile();
};

