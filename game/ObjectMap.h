#pragma once
#include "Utils.h"
#include "tinyxml.h"
#include "GameObject.h"
#include "Mario.h"
#include "FireBallPool.h"

class ObjectMap
{
	TiXmlElement* objectGroupElement;
	int objectGroupId;
	string name;
	CMario* mario;
	FireBallPool* pool;
public:
	ObjectMap(TiXmlElement* objectGroupElement, vector<LPGAMEOBJECT> &objects);
	void ImportData(vector<LPGAMEOBJECT>& objects);
};

