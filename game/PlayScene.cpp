#include <iostream>
#include <fstream>
#include "PlayScene.h"
#include "Utils.h"
#include "Sprites.h"
#include "Portal.h"
#include "Maps.h"
#include "BigBox.h"
#include "Ground.h"
#include "Item.h"
#include "Plant.h"
#include "Pipe.h"
#include "FireBall.h"
#include "MarioKickState.h"
#include "Camera.h"
#include "HUD.h"
#include "EffectPool.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	keyHandler = new CPlaySceneKeyHandler(this);
}

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAPS	7
#define SCENE_SECTION_FONT	8
#define SCENE_SECTION_HUD	9

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_ITEM	11
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_PLANT	6
#define OBJECT_TYPE_POOL_FIREBALL	68
#define OBJECT_TYPE_POOL_EFFECT	69
#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return;

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 6) return;

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return;

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; 

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return;

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
	{
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = CMario::GetInstance();

		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object created!\n");
	}
		break;
	case OBJECT_TYPE_POOL_FIREBALL:
		FireBallPool::GetInstance()->InitPool(objects);
		break;
	case OBJECT_TYPE_POOL_EFFECT:
		EffectPool::GetInstance()->InitPool(objects);
		break;
	/*case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;*/
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	if (obj != NULL) //check if not a pool
	{
		obj->SetPosition(x, y);

		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);
	}	
}

void CPlayScene::_ParseSection_FONT(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;

	string name = tokens[0].c_str();
	int spriteId = atoi(tokens[1].c_str());

	fontManager->GetInstance()->characters[name] = spriteId;
}

void CPlayScene::_ParseSection_HUD(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() != 1) return;

	int spriteId = atoi(tokens[0].c_str());

	HUD::GetInstance()->SetSpriteId(spriteId);
}

void CPlayScene::_ParseSection_MAPS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return;

	int id = atoi(tokens[0].c_str());
	const char* pathTmx = tokens[1].c_str();
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	tileMap = new TileMap();
	tileMap->GetInstance()->ReadFileTmx(pathTmx, id, D3DCOLOR_XRGB(R, G, B), objects, player);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAPS; continue;
		}
		if (line == "[FONT]") {
			section = SCENE_SECTION_FONT; continue;
		}
		if (line == "[HUD]") {
			section = SCENE_SECTION_HUD; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAPS: _ParseSection_MAPS(line); break;
		case SCENE_SECTION_FONT: _ParseSection_FONT(line); break;
		case SCENE_SECTION_HUD: _ParseSection_HUD(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObject;
	for (size_t i = 1; i < objects.size(); i++)
	{
		if (objects[i]->die == false)
			coObject.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->die == false)
			objects[i]->Update(dt, &coObject);
	}
	FireBallPool::GetInstance()->GetBackToPool();
	EffectPool::GetInstance()->GetBackToPool();
	HUD::GetInstance()->Update();

	//DebugOut(L"size coo: %d\n", coObject.size());
	//DebugOut(L"size: %d\n", objects.size());
}

void CPlayScene::Render()
{
	tileMap->GetInstance()->RenderBackground();

	int marioId = 0;
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<CMario*>(objects[i]))
			marioId = i;
		else if (objects[i]->die == false)
			objects[i]->Render();
	}	
	objects[marioId]->Render();

	tileMap->GetInstance()->RenderForeground();

	HUD::GetInstance()->Render();
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	objects.clear();

	player = NULL;
	tileMap = NULL;
	fontManager = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlaySceneKeyHandler::OnKeyDown(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scene)->GetPlayer();
	Input input = NO_INPUT;
	
	switch (KeyCode)
	{
	case DIK_S:
		input = PRESS_S;
		break;
	case DIK_F1:
		mario->Reset();
		break;
	case DIK_F2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		mario->y -= MARIO_BIG_BBOX_HEIGHT;
		mario->isUntouchable = false;
		break;
	case DIK_F3:
		mario->SetLevel(MARIO_LEVEL_RACCOON);
		mario->y -= MARIO_RACCOON_BBOX_HEIGHT;
		mario->isUntouchable = false;
		break;
	case DIK_F4:
		mario->SetLevel(MARIO_LEVEL_FIRE);
		mario->y -= MARIO_BIG_BBOX_HEIGHT;
		mario->isUntouchable = false;
		break;
	case DIK_F5:
		mario->SetLevel(MARIO_LEVEL_RACCOON);
		mario->y -= MARIO_RACCOON_BBOX_HEIGHT;
		mario->isUntouchable = true;
		break;
	case DIK_DOWN:
		input = PRESS_DOWN;
		break;
	case DIK_A:
		input = PRESS_A;
		break;
	case DIK_LEFT:
		input = PRESS_LEFT;
		break;
	case DIK_RIGHT:
		input = PRESS_RIGHT;
		break;
	}

	if (input != NO_INPUT)
		mario->HandleInput(input);
}

void CPlaySceneKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scene)->GetPlayer();
	Input input = NO_INPUT;
	
	switch (KeyCode)
	{
	case DIK_DOWN:
		input = RELEASE_DOWN;
		break;
	case DIK_A:
		input = RELEASE_A;
		break;
	case DIK_S:
		input = RELEASE_S;
		break;
	case DIK_LEFT:
		input = RELEASE_LEFT;
		break;
	case DIK_RIGHT:
		input = RELEASE_RIGHT;
		break;
	}

	if (input != NO_INPUT)
		mario->HandleInput(input);
}

void CPlaySceneKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scene)->GetPlayer();

	if (mario->GetState() == MARIO_STATE_DIE) return;

	Input input = KEY_STATE;

	mario->HandleInput(input);
}
