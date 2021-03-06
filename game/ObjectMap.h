#pragma once
#include "Utils.h"
#include "tinyxml.h"
#include "GameObject.h"

class ObjectMap
{
	TiXmlElement* objectGroupElement;
	int objectGroupId;
	string name;
public:
	ObjectMap(TiXmlElement* objectGroupElement, vector<LPGAMEOBJECT> &objects);
	void ImportData(vector<LPGAMEOBJECT>& objects);
};

