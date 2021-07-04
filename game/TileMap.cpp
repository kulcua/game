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

void TileMap::ReadFileTmx(const char* pathTmx, int id, D3DCOLOR transColor, vector<LPGAMEOBJECT> &objects, string prefixPath)
{
	TiXmlDocument doc(pathTmx);
	if (!doc.LoadFile())
	{
		return;
	}
	TiXmlElement* root = doc.RootElement(); //map
	TiXmlElement* element = root->FirstChildElement();

	while (element)
	{
		string elementName;
		elementName = element->Value();
		if (elementName.compare("tileset") == 0)
		{
			tileSet = new Tileset(element, id, transColor, prefixPath);
		}
		else if (elementName.compare("layer") == 0)
		{
			Layer* layer = new Layer(element);
			layers.push_back(layer);

			if (layer->GetName().compare("Foreground") == 0)
				foregroundLayer = layer;
		}
		else if (elementName.compare("objectgroup") == 0)
		{
			objectMap = new ObjectMap(element, objects, grid);
		}
		element = element->NextSiblingElement();
	}
}

void TileMap::RenderBackground()
{
	for (int i = 0; i < layers.size(); i++)
	{
		if (layers[i]->GetName().compare("Foreground") != 0)
			layers[i]->Render();
	}
}

void TileMap::RenderForeground()
{
	if (foregroundLayer != NULL)
		foregroundLayer->Render();
}

void TileMap::Clear()
{
	foregroundLayer = NULL;
	objectMap = NULL;
	tileSet = NULL;

	for (int i = 0; i < layers.size(); i++)
	{
		delete layers[i];
	}
	layers.clear();
}