#include "Layer.h"

Layer::Layer(TiXmlElement* layer)
{
	this->layerElement = layer;
	this->dataElement = layer->FirstChildElement();
	ImportData();
}

void Layer::ImportData()
{
	string s = dataElement->GetText();
	vector<string> vt = split(s, ",");
	for (int i = 0; i < vt.size(); i++)
	{
		dataCsv.push_back(atoi(vt[i].c_str()));
	}
}