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

bool TileMap::ReadFileTmx(const char* pathTmx, int id, D3DCOLOR transColor, vector<LPGAMEOBJECT> &objects, CMario *mario)
{
	TiXmlDocument doc(pathTmx);
	if (!doc.LoadFile())
	{
		return -1;
	}
	TiXmlElement* root = doc.RootElement(); //map
	TiXmlElement* editorsSettingsElement = root->FirstChildElement();

	string elementName;
	TiXmlElement* element = editorsSettingsElement->NextSiblingElement();
	
	while (element)
	{
		elementName = element->Value();
		if (elementName.compare("tileset") == 0)
		{
			tileSet = new Tileset(element, id, transColor);
		}
		else if (elementName.compare("layer") == 0)
		{
			Layer* layer = new Layer(element);
			layers.push_back(layer);
		}
		else if (elementName.compare("objectgroup") == 0)
		{
			objectMap = new ObjectMap(element, objects);
		}
		element = element->NextSiblingElement();
	}
	return true;
}

void TileMap::Render()
{
	for (int i = 0; i < layers.size(); i++)
	{
		if (layers[i]->GetName().compare("Foreground") == 0)
			foreground = layers[i];
		else layers[i]->Render();
	}
}

void TileMap::RenderForeground()
{
	foreground->Render();
}