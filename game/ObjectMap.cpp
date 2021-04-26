#include "ObjectMap.h"
#include "Ground.h"
#include "BigBox.h"
#include "Brick.h"
#include "CameraBound.h"
#include "Camera.h"
#include "Goomba.h"
#include "VenusFireTrap.h"
#include "PiranhaPlant.h"
#include "ParaGoomba.h"
#include "ParaKoopa.h"
#include "KoopaBound.h"
#include "CoinBrick.h"
#include "PowerUpItem.h"
#include "BrickBlock.h"
#include "Coin.h"

ObjectMap::ObjectMap(TiXmlElement* objectGroupElement, vector<LPGAMEOBJECT> &objects)
{
	this->objectGroupElement = objectGroupElement;
	objectGroupElement->QueryIntAttribute("objectGroupId", &objectGroupId);
	name = objectGroupElement->Attribute("name");
	ImportData(objects);
	mario =mario->GetInstance();
	pool = FireBallPool::GetInstance();
}

void ObjectMap::ImportData(vector<LPGAMEOBJECT>& objects)
{
	CGameObject* obj = NULL;
	int objectId;
	float x, y;
	float width, height;
	TiXmlElement* element = objectGroupElement->FirstChildElement();
	if (name.compare("Solid") == 0)
	{					
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			element->QueryFloatAttribute("width", &width);
			element->QueryFloatAttribute("height", &height);
			obj = new CGround(width, height);
			obj->SetPosition(x, y);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}		
	}
	else if (name.compare("Ghost") == 0)
	{
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			element->QueryFloatAttribute("width", &width);
			element->QueryFloatAttribute("height", &height);
			obj = new CBigBox(width, height);
			obj->SetPosition(x, y);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Brick") == 0)
	{
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			obj = new BrickBlock();
			obj->SetPosition(x, y);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("QuestionBlocks") == 0)
	{
		string typeName;
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			typeName = element->Attribute("name");
			CBrick* br = new CBrick(x, y);
			CItem* item = NULL;
			if (typeName.compare("coin") == 0)
			{
				item = new CoinBrick();
			}
			else if (typeName.compare("powerup") == 0) 
			{
				item = new PowerUpItem();
			}
			if (item != NULL)
			{
				item->SetPosition(x, y);
				objects.push_back(item);
			}
			br->SetItem(item);
			objects.push_back(br);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Coin") == 0)
	{
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			obj = new Coin();
			obj->SetPosition(x, y);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("CameraBound") == 0)
	{
		int type;
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			element->QueryFloatAttribute("width", &width);
			element->QueryFloatAttribute("height", &height);
			element->QueryIntAttribute("type", &type);
			obj = new CCameraBound(width, height, type);
			obj->SetPosition(x, y);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Camera") == 0)
	{
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			element->QueryFloatAttribute("width", &width);
			element->QueryFloatAttribute("height", &height);
			obj = new CCamera(x, y, width, height);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("KoopaBound") == 0)
	{
		while (element)
		{
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);
			element->QueryFloatAttribute("width", &width);
			element->QueryFloatAttribute("height", &height);
			obj = new KoopaBound(width, height);
			obj->SetPosition(x, y);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Enemy") == 0)
	{				
		string enemyName;
		while (element)
		{
			enemyName = element->Attribute("name");
			element->QueryFloatAttribute("x", &x);
			element->QueryFloatAttribute("y", &y);

			TiXmlElement* properties = element->FirstChildElement();
			TiXmlElement* property = properties->FirstChildElement();
			int ani_id;
			property->QueryIntAttribute("value", &ani_id);

			if (enemyName.compare("goomba") == 0)
			{
				string type = element->Attribute("type");
				if (type.compare("tan") == 0)
					obj = new CGoomba();
				else if (type.compare("para") == 0)
					obj = new ParaGoomba();
			}
			else if (enemyName.compare("koopa") == 0)
			{
				string type = element->Attribute("type");
				if (type.compare("red") == 0)
					obj = new CKoopa();
				else if (type.compare("para") == 0)
					obj = new ParaKoopa();
			}
			else if (enemyName.compare("venus") == 0)
			{
				string type = element->Attribute("type");
				if (type.compare("red") == 0)
					obj = new VenusFireTrap(y, VENUS_RED_TYPE);
				else
					obj = new VenusFireTrap(y, VENUS_GREEN_TYPE);
			}
			else if (enemyName.compare("piranha") == 0)
			{
				obj = new PiranhaPlant(y);
			}

			DebugOut(L"name %s\n", ToLPCWSTR(enemyName));
			CAnimationSets* animation_sets = CAnimationSets::GetInstance();
			LPANIMATION_SET ani_set = animation_sets->Get(ani_id);
			obj->SetAnimationSet(ani_set);
			obj->SetPosition(x, y);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
}