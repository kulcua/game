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
#include "Game.h"
#include "KoopaBound.h"
#include "CoinBrick.h"
#include "PowerUpItem.h"
#include "BrotherBound.h"
#include "BrickBlock.h"
#include "Coin.h"
#include "GreenMushroom.h"
#include "SwitchItem.h"
#include "Card.h"
#include "PortalPipe.h"
#include "Portal.h"
#include "BoundOverWorld.h"
#include "BoomerangBrother.h"
#include "Tree.h"
#include "MusicalNote.h"
#include "BrickCoins.h"
#include "ParaMiniGoomba.h"

ObjectMap::ObjectMap(TiXmlElement* objectGroupElement, vector<LPGAMEOBJECT> &objects, Grid* grid)
{
	this->grid = grid;
	this->objectGroupElement = objectGroupElement;
	objectGroupElement->QueryIntAttribute("objectGroupId", &objectGroupId);
	name = objectGroupElement->Attribute("name");
	ImportData(objects);
}

void GetInfoElement(TiXmlElement* element, int &objectId, float &x, float &y, float &width, float &height)
{
	element->QueryIntAttribute("id", &objectId);
	element->QueryFloatAttribute("x", &x);
	element->QueryFloatAttribute("y", &y);
	element->QueryFloatAttribute("width", &width);
	element->QueryFloatAttribute("height", &height);
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
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new CGround(width, height);
			obj->SetPosition(x, y);
			obj->SetGrid(grid, objectId);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}		
	}
	else if (name.compare("BoundOverWorld") == 0)
	{
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new BoundOverWorld(width, height);
			obj->SetPosition(x, y);
			obj->SetGrid(grid, objectId);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Ghost") == 0)
	{
		while (element)
		{
			int type;
			GetInfoElement(element, objectId, x, y, width, height);
			CBigBox* obj = new CBigBox(width, height);
			element->QueryIntAttribute("type", &type);
			obj->SetType(type);
			obj->SetPosition(x, y);
			obj->SetGrid(grid, objectId);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Brick") == 0)
	{
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new BrickBlock();
			obj->SetPosition(x, y);
			obj->SetGrid(grid, objectId);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Card") == 0)
	{
		GetInfoElement(element, objectId, x, y, width, height);
		obj = new Card();
		obj->SetPosition(x, y);
		obj->SetGrid(grid, objectId);
		objects.push_back(obj);
		element = element->NextSiblingElement();
	}
	else if (name.compare("QuestionBlocks") == 0)
	{
		while (element)
		{
			bool coins = false;
			string typeName;
			int type;
			GetInfoElement(element, objectId, x, y, width, height);
			typeName = element->Attribute("name");
			element->QueryIntAttribute("type", &type);
			CBrick* br = new CBrick(type, x, y);
			CItem* item = NULL;
			if (typeName.compare("coin") == 0)
			{
				item = new CoinBrick();
			}
			else if (typeName.compare("powerup") == 0) 
			{
				item = new PowerUpItem();
			}
			else if (typeName.compare("1upMushroom") == 0)
			{
				item = new GreenMushroom(y);
			}
			else if (typeName.compare("switch") == 0)
			{
				item = new SwitchItem();
				y -= ITEM_BBOX_HEIGHT;
			}
			else if (typeName.compare("coin10") == 0)
			{
				vector<CItem*> listItems;
				BrickCoins* brCoins = new BrickCoins(type, x, y);
				for (int i = 0; i < BRICK_STATE_NUM_COINS; i++)
				{
					CItem* item = new CoinBrick();
					item->SetPosition(x, y);
					item->SetGrid(grid, objectId);
					objects.push_back(item);
					listItems.push_back(item);
				}
				brCoins->SetListItems(listItems);
				brCoins->SetGrid(grid, objectId);
				objects.push_back(brCoins);
				coins = true;
			}
			if (coins == false)
			{
				item->SetPosition(x, y);
				br->SetItem(item);
				item->SetGrid(grid, objectId);
				objects.push_back(item);
				br->SetGrid(grid, objectId);
				objects.push_back(br);
			}
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Coin") == 0)
	{
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new Coin();
			obj->SetPosition(x, y);
			obj->SetGrid(grid, objectId);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("MusicalNote") == 0)
	{
		while (element)
		{
			int type;
			GetInfoElement(element, objectId, x, y, width, height);
			element->QueryIntAttribute("type", &type);
			obj = new MusicalNote(type, y);
			obj->SetPosition(x, y);
			obj->SetGrid(grid, objectId);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("CameraBound") == 0)
	{
		while (element)
		{
			int type;
			GetInfoElement(element, objectId, x, y, width, height);
			element->QueryIntAttribute("type", &type);
			obj = new CCameraBound(type, width, height);
			obj->SetPosition(x, y);
			obj->SetGrid(grid, objectId);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Camera") == 0)
	{
		while (element)
		{
			int isMove;
			element->QueryFloatAttribute("y", &y);
			element->QueryIntAttribute("type", &isMove);
			CCamera* cam = new CCamera();
			CGame::GetInstance()->SetCam(cam);
			cam->SetPosition(y);
			cam->SetIsMove(isMove);
			objects.push_back(cam);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("KoopaBound") == 0)
	{
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new KoopaBound(width, height);
			obj->SetPosition(x, y);
			obj->SetGrid(grid, objectId);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("BrotherBound") == 0)
	{
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new BrotherBound(width, height);
			obj->SetPosition(x, y);
			obj->SetGrid(grid, objectId);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Enemy") == 0)
	{		
		while (element)
		{
			string enemyName;
			enemyName = element->Attribute("name");
			GetInfoElement(element, objectId, x, y, width, height);

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
				else if (type.compare("paramini") == 0)
					obj = new ParaMiniGoomba();
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
			else if (enemyName.compare("boomerangbrother") == 0)
			{
				obj = new BoomerangBrother();
			}

			CAnimationSets* animation_sets = CAnimationSets::GetInstance();
			LPANIMATION_SET ani_set = animation_sets->Get(ani_id);
			obj->SetAnimationSet(ani_set);
			obj->SetPosition(x, y);
			obj->SetGrid(grid, objectId);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Portal") == 0)
	{
		while (element)
		{
			string name;
			int type;
			float camY = 0;
			GetInfoElement(element, objectId, x, y, width, height);
			name = element->Attribute("name");
			element->QueryIntAttribute("type", &type);
			if (name.compare("out") == 0)
			{
				TiXmlElement* propCam = element->FirstChildElement()->FirstChildElement();
				propCam->QueryFloatAttribute("value", &camY);
			}
			obj = new PortalPipe(name, type, camY, width, height);
			obj->SetPosition(x, y);
			obj->SetGrid(grid, objectId);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("WorldGraph") == 0)
	{
		while (element)
		{
			string type;
			GetInfoElement(element, objectId, x, y, width, height);
			if (element->Attribute("type"))
			{
				type = element->Attribute("type");
			}
			else type = "node";
			obj = new CPortal(type);
			obj->SetPosition(x - PORTAL_WIDTH / 2, y - PORTAL_HEIGHT / 2);
			obj->SetGrid(grid, objectId);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("AnimatedBG") == 0)
	{ //tree overworld
		while (element)
		{
			string name;
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new Tree();
			obj->SetPosition(x - TREE_WIDTH / 2, y - TREE_HEIGHT / 2);
			obj->SetGrid(grid, objectId);
			objects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
}