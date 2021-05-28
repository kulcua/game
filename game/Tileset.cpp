#include "Tileset.h"
#include "Textures.h"
#include "Sprites.h"

Tileset::Tileset(TiXmlElement* tileset, int id, D3DCOLOR transColor, string prefixPath)
{
	this->tileset = tileset;
	this->textureId = id;
	this->transColor = transColor;
	this->prefixPath = prefixPath;
	SplitImageToTile();
}

void Tileset::SplitImageToTile()
{
	tileset->QueryIntAttribute("tilewidth", &tileWidth);
	tileset->QueryIntAttribute("tileheight", &tileHeight);
	tileset->QueryIntAttribute("tilecount", &tileCount);
	tileset->QueryIntAttribute("columns", &columns);
	rows = tileCount / columns;

	TiXmlElement* image = tileset->FirstChildElement();
	pathImage = ToLPCWSTR(prefixPath + image->Attribute("source"));

	CTextures::GetInstance()->Add(textureId, pathImage, transColor);
	LPDIRECT3DTEXTURE9 texMap = CTextures::GetInstance()->Get(textureId);

	int spriteId = 1;	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			CSprites::GetInstance()->Add(spriteId, tileHeight * j, tileWidth * i, tileHeight * (j + 1), tileWidth * (i + 1), texMap);
			spriteId++;
		}
	}
}