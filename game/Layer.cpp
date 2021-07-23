#include "Layer.h"
#include "Sprites.h"
#include "Game.h"

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
	float cx, cy;
	CGame::GetInstance()->GetCam()->GetPosition(cx, cy);
	int tileStartX = (int)cx / TILE_SIZE;
	int tileStartY = (int)cy / TILE_SIZE;
	int tileEndX = (int)(cx + CAM_WIDTH) / TILE_SIZE + 1;
	int tileEndY = (int)(cy + CAM_HEIGHT) / TILE_SIZE + 1;

	if (tileStartX < 0) tileStartX = 0;
	if (tileStartY < 0) tileStartY = 0;

	if (isVisible)
	{
		for (int i = tileStartY; i < tileEndY; i++)
		{
			for (int j = tileStartX; j < tileEndX; j++)
			{
				if (tile[i][j] != 0)
				{
					CSprites::GetInstance()->Get(tile[i][j])->Draw((float)j * TILE_SIZE, (float)i * TILE_SIZE, -1, -1);
				}
			}
		}
	}			
}