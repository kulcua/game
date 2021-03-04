#pragma once
#include "fstream"
#include "Utils.h"
#include "tinyxml.h"

class Layer
{
	TiXmlElement* layerElement;
	TiXmlElement* dataElement;

	int layerId;
	string name;
	int width;
	int height;

	vector<int> dataCsv;
public:
	Layer(TiXmlElement* layerElement);
	void ImportData();
};