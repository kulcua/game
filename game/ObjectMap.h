#pragma once
#include "Utils.h"
#include "tinyxml.h"
#include "GameObject.h"
#include "Mario.h"

class ObjectMap
{
	TiXmlElement* objectGroupElement;
	int objectGroupId;
	string name;
	CMario* mario;
public:
	ObjectMap(TiXmlElement* objectGroupElement, vector<LPGAMEOBJECT> &objects, CMario *mario);
	void ImportData(vector<LPGAMEOBJECT>& objects);
};

