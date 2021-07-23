#include "MarioStandingState.h"
#include "Mario.h"
#include "MarioRunningState.h"
#include "MarioFrontState.h"

MarioStandingState* MarioStandingState::__instance = NULL;

MarioStandingState* MarioStandingState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioStandingState();
    }
	return __instance;
}

void MarioStandingState::HandleInput(CMario& mario, Input input)
{
    if (input == Input::PRESS_DOWN && MarioFrontState::GetInstance()->onPortalPipe)
    {
        mario.state_ = MarioState::front.GetInstance();
    }
    else {
        MarioOnGroundState::HandleInput(mario, input);
    }
}

void MarioStandingState::Enter(CMario& mario) 
{
    if (mario.isHandleShell)
    {
        if (mario.GetLevel() == MARIO_LEVEL_SMALL)
        {
            mario.SetAnimation(MARIO_ANI_SMALL_HANDLESHELL_IDLE);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_BIG)
        {
            mario.SetAnimation(MARIO_ANI_BIG_HANDLESHELL_IDLE);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        {
            mario.SetAnimation(MARIO_ANI_RACCOON_HANDLESHELL_IDLE);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
        {
            mario.SetAnimation(MARIO_ANI_FIRE_HANDLESHELL_IDLE);
        }
    }
    else
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
        else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
        {
            mario.SetAnimation(MARIO_ANI_FIRE_IDLE);
        }
    }
}

void MarioStandingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioStandingState::Update(CMario& mario, DWORD dt)
{
    if (mario.vx !=0)
    {
        mario.state_ = MarioState::running.GetInstance();
    }
    if (mario.isHandleShell == true)
    {
        mario.PowerReset();
        mario.isPower = true; // cuz standing but player still keep PRESS_A
    }       
    //DebugOut(L"MarioStandingState %f %f\n", mario.x, mario.y);
}