#include "ObjectMap.h"
#include "Ground.h"
#include "BigBox.h"
#include "Brick.h"

ObjectMap::ObjectMap(TiXmlElement* objectGroupElement, vector<LPGAMEOBJECT> &objects)
{
	DebugOut(L"objectgroup\n");
	this->objectGroupElement = objectGroupElement;
	objectGroupElement->QueryIntAttribute("objectGroupId", &objectGroupId);
	name = objectGroupElement->Attribute("name");

	ImportData(objects);
}

void ObjectMap::ImportData(vector<LPGAMEOBJECT>& objects)
{
	CGameObject* obj = NULL;
	int objectId;
	float x, y;
	float width, height;
	if (name.compare("Solid") == 0)
	{				
		TiXmlElement* element = objectGroupElement->FirstChildElement();		
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			element->QueryFloatAttribute("width", &width);
			element->QueryFloatAttribute("height", &height);
			obj = new CGround(x, y, width, height);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}		
	}
	else if (name.compare("Ghost") == 0)
	{
		TiXmlElement* element = objectGroupElement->FirstChildElement();
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			element->QueryFloatAttribute("width", &width);
			element->QueryFloatAttribute("height", &height);
			obj = new CBigBox(x, y, width, height);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("QuestionBlocks") == 0)
	{
		string typeName;
		int type;
		TiXmlElement* element = objectGroupElement->FirstChildElement();
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			element->QueryIntAttribute("type", &type);
			//typeName = objectGroupElement->Attribute("name");
			obj = new CBrick(x, y, type);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
}