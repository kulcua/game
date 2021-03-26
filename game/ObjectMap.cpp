#include "ObjectMap.h"
#include "Ground.h"
#include "BigBox.h"
#include "Brick.h"
#include "CameraBound.h"
#include "Camera.h"
#include "Goomba.h"

ObjectMap::ObjectMap(TiXmlElement* objectGroupElement, vector<LPGAMEOBJECT> &objects, CMario* mario)
{
	this->objectGroupElement = objectGroupElement;
	objectGroupElement->QueryIntAttribute("objectGroupId", &objectGroupId);
	name = objectGroupElement->Attribute("name");
	this->mario = mario;
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
		TiXmlElement* element = objectGroupElement->FirstChildElement();
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			typeName = objectGroupElement->Attribute("name");

			if (typeName.compare("powerup") == 0)
			{
				
			}

			obj = new CBrick(x, y, typeName);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("CameraBound") == 0)
	{
		int type;
		TiXmlElement* element = objectGroupElement->FirstChildElement();
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			element->QueryFloatAttribute("width", &width);
			element->QueryFloatAttribute("height", &height);
			element->QueryIntAttribute("type", &type);
			obj = new CCameraBound(x, y, width, height, type);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Camera") == 0)
	{
		TiXmlElement* element = objectGroupElement->FirstChildElement();
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			element->QueryFloatAttribute("width", &width);
			element->QueryFloatAttribute("height", &height);
			obj = new CCamera(mario, x, y, width, height);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Enemy") == 0)
	{		
		TiXmlElement* element = objectGroupElement->FirstChildElement();		
		string enemyName;
		while (element)
		{
			enemyName = element->Attribute("name");
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);

			if (enemyName.compare("goomba") == 0)
			{
				obj = new CGoomba();

				TiXmlElement* properties = element->FirstChildElement();
				TiXmlElement* property = properties->FirstChildElement();
				int ani_id;
				property->QueryIntAttribute("value", &ani_id);

				CAnimationSets* animation_sets = CAnimationSets::GetInstance();
				LPANIMATION_SET ani_set = animation_sets->Get(ani_id);
				obj->SetAnimationSet(ani_set);
				obj->SetPosition(x, y);
				objects.push_back(obj);
			}
			element = element->NextSiblingElement();
		}
	}
}