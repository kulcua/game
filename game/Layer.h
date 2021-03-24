#pragma once
#include "fstream"
#include "Utils.h"
#include "tinyxml.h"

#define MAX_TILE 200
#define TILE_SIZE 48

class Layer
{
	TiXmlElement* layerElement;
	TiXmlElement* dataElement;

	int layerId;
	string name;
	int width;
	int height;
	int isVisible;

	int tile[MAX_TILE][MAX_TILE];
public:
	Layer(TiXmlElement* layerElement);
	void ImportData();
	void Render();
};