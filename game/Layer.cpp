#include "Layer.h"
#include "Sprites.h"

Layer::Layer(TiXmlElement* layerElement)
{
	this->layerElement = layerElement;
	layerElement->QueryIntAttribute("id", &layerId);
	name = layerElement->Attribute("name");
	layerElement->QueryIntAttribute("width", &width);
	layerElement->QueryIntAttribute("height", &height);
	if (layerElement->Attribute("visible") == NULL)
		isVisible = 1;
	else 
		layerElement->QueryIntAttribute("visible", &isVisible);

	this->dataElement = layerElement->FirstChildElement();

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
	if (isVisible)
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
}