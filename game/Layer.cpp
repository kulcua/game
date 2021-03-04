#include "Layer.h"
#include "Sprites.h"

Layer::Layer(TiXmlElement* layer)
{
	this->layerElement = layer;	
	layer->QueryIntAttribute("id", &layerId);
	name = layer->Attribute("name");
	layer->QueryIntAttribute("width", &width);
	layer->QueryIntAttribute("height", &height);

	this->dataElement = layer->FirstChildElement();

	ImportData();
}

void Layer::ImportData()
{
	string s = dataElement->GetText();
	vector<string> vt = split(s, ",");
	int index = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			tile[i][j] = atoi(vt[index].c_str());
			index++;
		}
	}
}

void Layer::Render()
{	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (tile[i][j] != 0)
			{
				CSprites::GetInstance()->Get(tile[i][j])->Draw(j * TILE_SIZE, i * TILE_SIZE, NULL);
			}
		}
	}		
}