#include "Intro.h"
#include "MarioState.h"
#include "MarioWalkingState.h"
#include "Game.h"
#include "MarioSittingState.h"
#include "MarioJumpingState.h"
#include "MarioStandingState.h"

Intro* Intro::__instance = NULL;

Intro* Intro::GetInstance()
{
	if (__instance == NULL) __instance = new Intro();
	return __instance;
}

void Intro::SetScenario(vector<LPGAMEOBJECT> &objects)
{
	introTimeStart = GetTickCount64();

	this->objects = objects;
	mario = new CMario();
	mario->SetLevel(MARIO_LEVEL_BIG);
	mario->SetPosition(700, 400);
	mario->nx = -1;
	this->objects.push_back(mario);

	luigi = new CMario();
	luigi->SetLevel(MARIO_LEVEL_BIG);
	luigi->SetPosition(0, 400);
	luigi->nx = 1;
	this->objects.push_back(luigi);

	cam = new CCamera();
	CGame::GetInstance()->SetCam(cam);

	curtain = new Curtain();
	this->objects.push_back(curtain);

	three = new Three(curtain);
	this->objects.push_back(three);

	arrow = new Arrow();
	arrow->SetPosition(210, 428);
	this->objects.push_back(arrow);
}

void Intro::PhaseIntro()
{
	ULONGLONG timePassed = GetTickCount64() - introTimeStart;
	if (timePassed < 3000)
	{
		//stop roll curtain
	}
	else if (timePassed < 4500)
	{
		//mario walking
		mario->vx = -MARIO_WALKING_SPEED;
		luigi->vx = MARIO_WALKING_SPEED;
		luigi->state_ = MarioState::walking.GetInstance();
		mario->state_ = MarioState::walking.GetInstance();
	}
	else if (timePassed < 6000)
	{
		if (luigi_jump_mario == false)
		{
			mario->state_ = MarioState::sitting.GetInstance();
			mario->vx = 0;

			luigi->isOnGround = false;
			luigi->state_ = MarioState::jumping.GetInstance();
			MarioState::jumping.GetInstance()->StartJump();
			luigi->vy = -1.3f;
			luigi->vx = 0.1f;
			luigi_jump_mario = true;
		}
	}
	else if (timePassed < 6500)
	{
		if (luigi_high_jump == false)
		{
			luigi->isOnGround = false;
			luigi->state_ = MarioState::jumping.GetInstance();
			MarioState::jumping.GetInstance()->StartJump();
			luigi->vy = -1.0f;
			luigi_high_jump = true;
		}
	}
	else if (timePassed < 9000)
	{
		if (luigi->isOnGround == true)
		{
			luigi->state_ = MarioState::walking.GetInstance();
			luigi->vx = 0.1f;
		}
	}
	else if (timePassed < 9100)
	{
		if (luigi->die == false)
		{
			luigi->die = true;
			mario->die = true;
			curtain->ani = CURTAIN_ANI_BROS;
			curtain->SetPosition(0, -500);
			curtain->vy = 0.2f;
			three->SetPosition(350, -230);
			three->die = false;
		}
	}

	if (mario->die == false)
		mario->state_->Enter(*mario);
	if (luigi->die == false)
		luigi->state_->Enter(*luigi);
}

void Intro::Update(DWORD dt)
{
	PhaseIntro();

	cam->vx = 0;
	cam->vy = 0;

	if (three->isStop && turnOnBG == false) {
		turnOnBG = true;
		arrow->die = false;
		CGame::GetInstance()->SetBackgroundColor(D3DCOLOR_XRGB(255, 216, 154));
	}

	vector<CGameObject*> coObjects;

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->die == false)
			coObjects.push_back(objects[i]);
	}
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->die == false)
			objects[i]->Update(dt, &coObjects);
	}
}

void Intro::Render()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->die == false)
			objects[i]->Render();
	}

	if (turnOnBG)
	{
		CSprites::GetInstance()->Get(INTRO_PLAYER_GAME)->Draw(250, 430, -1, -1, 255);
		CSprites::GetInstance()->Get(INTRO_CURTAIN)->Draw(0, 0, -1, -1, 255);
		CSprites::GetInstance()->Get(INTRO_TREE_LEFT)->Draw(600, 260, -1, -1, 255);
		CSprites::GetInstance()->Get(INTRO_TREE_RIGHT)->Draw(0, 360, -1, -1, 255);
		CSprites::GetInstance()->Get(INTRO_CLOUD_BIG)->Draw(100, 100, -1, -1, 255);
		CSprites::GetInstance()->Get(INTRO_CLOUD_SMALL)->Draw(0, 280, -1, -1, 255);
		CSprites::GetInstance()->Get(INTRO_CLOUD_BIG)->Draw(600, 80, -1, -1, 255);
	}
}

void Intro::ArrowUp()
{
	arrow->SetPosition(210, 428);
}

void Intro::ArrowDown()
{
	arrow->SetPosition(210, 475);
}

void Intro::SwitchOverWorld()
{
	CGame::GetInstance()->SwitchScene(WORLD_MAP_SCENE);
}
