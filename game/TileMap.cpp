#include "TileMap.h"
#include "Textures.h"
#include "Sprites.h"

using namespace std;

TileMap* TileMap::__instance = NULL;

TileMap* TileMap::GetInstance()
{
	if (__instance == NULL) __instance = new TileMap();
	return __instance;
}

bool TileMap::ReadFileTmx(const char* pathTmx, int id, D3DCOLOR transColor)
{
	TiXmlDocument doc(pathTmx);
	if (!doc.LoadFile())
	{
		return -1;
	}
	TiXmlElement* root = doc.RootElement(); //map
	TiXmlElement* editorsettings = root->FirstChildElement();

	TiXmlElement* tileset = editorsettings->NextSiblingElement();

	tileSet = new Tileset(tileset, id, transColor);
	
	return true;
}