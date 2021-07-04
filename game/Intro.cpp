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

void Intro::SetScenario(vector<LPGAMEOBJECT> &objects)
{
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();;
	mario->SetLevel(MARIO_LEVEL_BIG);
	mario->SetPosition(700, 400);
	mario->nx = -1;
	mario->state_ = MarioState::walking.GetInstance();
	mario->state_->Enter(*mario);
	objects.push_back(mario);

	luigi->SetLevel(MARIO_LEVEL_BIG);
	luigi->SetPosition(0, 400);
	luigi->nx = 1;
	luigi->state_ = MarioState::walking.GetInstance();
	luigi->state_->Enter(*luigi);
	objects.push_back(luigi);
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
			DebugOut(L"mario\n");
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

void Intro::Update()
{
	Step1();
	//DebugOut(L"level %d %d\n", mario->GetLevel(), mario->GetAnimation());
}