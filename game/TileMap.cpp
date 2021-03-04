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
	TiXmlElement* editorsSettingsElement = root->FirstChildElement();

	string nameElement;
	TiXmlElement* nextElement = editorsSettingsElement->NextSiblingElement();
	
	while (nextElement)
	{
		nameElement = nextElement->Value();
		if (nameElement.compare("tileset") == 0)
		{
			DebugOut(L"Tileset\n");
			this->tileSet = new Tileset(nextElement, id, transColor);			
		}
		else if (nameElement.compare("layer") == 0)
		{
			DebugOut(L"Layer\n");
			this->layer = new Layer(nextElement);			
		}
		nextElement = nextElement->NextSiblingElement();
	}
	DebugOut(L"null\n");
	//TiXmlElement* tilesetElement = editorsSettingsElement->NextSiblingElement();
	//TiXmlElement* layerElement = tilesetElement->NextSiblingElement();
	////TiXmlElement* objectGroupElement = layerElement->NextSiblingElement();
	//DebugOut(L"nee %s\n", ToLPCWSTR(s));	
	return true;
}