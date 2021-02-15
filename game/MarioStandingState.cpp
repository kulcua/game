#include "MarioStandingState.h"
#include "Utils.h"
#include "Mario.h"
#include "MarioDuckingState.h"
#include "Game.h"

MarioStandingState* MarioStandingState::__instance = NULL;

MarioStandingState* MarioStandingState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioStandingState();
        DebugOut(L"Init MarioStandingState\n");
    }
	return __instance;
}

void MarioStandingState::HandleInput(CMario& mario)
{
    CGame* game = CGame::GetInstance();
    if (game->IsKeyDown(DIK_DOWN))
    {
        //DebugOut(L"ducking \n");
        mario.state_ = MarioState::ducking.GetInstance();
    }
    else 
    {
        // Didn't handle input, so walk up hierarchy.
        MarioOnGroundState::HandleInput(mario);
    }
}

void MarioStandingState::Enter(CMario& mario) // declare (CMario& mario) means in CMario has a friend class MarioStandingState
{
    if (mario.GetLevel() == MARIO_LEVEL_SMALL)
    {
        mario.SetAnimation(MARIO_ANI_SMALL_IDLE);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_BIG_IDLE);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_RACCOON_IDLE);
    }
}

void MarioStandingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioStandingState::Update(CMario& mario)
{
    //mario.vx = 0;
}