#include "Intro.h"
#include "MarioState.h"
#include "MarioWalkingState.h"
#include "Game.h"
#include "MarioSittingState.h"
#include "MarioJumpingState.h"

Intro* Intro::__instance = NULL;

Intro* Intro::GetInstance()
{
	if (__instance == NULL) __instance = new Intro();
	return __instance;
}

Intro::Intro(){}

void Intro::SetScenario(vector<LPGAMEOBJECT> &objects)
{
	this->objects = objects;
	mario = new CMario();
	mario->SetLevel(MARIO_LEVEL_BIG);
	mario->SetPosition(700, 400);
	mario->nx = -1;
	mario->state_ = MarioState::walking.GetInstance();
	mario->state_->Enter(*mario);
	this->objects.push_back(mario);

	luigi = new CMario();
	luigi->SetLevel(MARIO_LEVEL_BIG);
	luigi->SetPosition(0, 400);
	luigi->nx = 1;
	luigi->state_ = MarioState::walking.GetInstance();
	luigi->state_->Enter(*luigi);
	this->objects.push_back(luigi);

	cam = new CCamera();
	CGame::GetInstance()->SetCam(cam);
	DebugOut(L"cam %f %f\n", cam->x, cam->y);
}

void Intro::Step1() {
	float xCenter = CGame::GetInstance()->GetScreenWidth() / 2;
	if (luigi_jump_mario == false)
	{
		if (mario->x <= xCenter)
		{
			mario->state_ = MarioState::sitting.GetInstance();
			mario->state_->Enter(*mario);
			mario->vx = 0;
			luigi_jump_mario = true;
		}
		else {
			mario->vx = -MARIO_WALKING_SPEED;
		}

		if (luigi->x >= xCenter - 100)
		{
			luigi->state_ = MarioState::jumping.GetInstance();
			luigi->state_->Enter(*luigi);
			luigi_jump_mario = true;
			luigi->vy = -0.7f;
			DebugOut(L"luigi\n");
		}
		else {
			luigi->vx = MARIO_WALKING_SPEED;
		}
	}
}

void Intro::Update(DWORD dt)
{
	vector<CGameObject*> coObjects;
	Step1();
	cam->vx = 0;
	cam->vy = 0;
	for (int i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
}

void Intro::Render()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
}