#pragma once
#include "Utils.h"
#include "tinyxml.h"
#include "GameObject.h"

class ObjectMap
{
	TiXmlElement* objectGroupElement;
	int objectGroupId;
	string name;
	Grid* grid;
public:
	ObjectMap(TiXmlElement* objectGroupElement, vector<LPGAMEOBJECT> &objects, Grid* grid);
	void ImportData(vector<LPGAMEOBJECT>& objects);
};

