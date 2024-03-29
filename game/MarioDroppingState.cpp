#include "MarioDroppingState.h"
#include "Mario.h"
#include "Game.h"
#include "MarioStandingState.h"
#include "MarioDropFlyState.h"
#include "MarioWalkingState.h"

MarioDroppingState* MarioDroppingState::__instance = NULL;

MarioDroppingState* MarioDroppingState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioDroppingState();
    }
    return __instance;
}

void MarioDroppingState::Enter(CMario& mario)
{
    if (mario.isHandleShell)
    {
        if (mario.GetLevel() == MARIO_LEVEL_SMALL)
        {
            mario.SetAnimation(MARIO_ANI_SMALL_HANDLESHELL_JUMP_DROP);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_BIG)
        {
            mario.SetAnimation(MARIO_ANI_BIG_HANDLESHELL_JUMP_DROP);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        {
            mario.SetAnimation(MARIO_ANI_RACCOON_HANDLESHELL_JUMP_FLY_DROP);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
        {
            mario.SetAnimation(MARIO_ANI_FIRE_HANDLESHELL_JUMP_DROP);
        }
    }
    else
    {
        if (mario.GetLevel() == MARIO_LEVEL_SMALL)
        {
            mario.SetAnimation(MARIO_ANI_SMALL_DROP);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_BIG)
        {
            mario.SetAnimation(MARIO_ANI_BIG_DROP);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        {
            mario.SetAnimation(MARIO_ANI_RACCOON_DROP);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
        {
            mario.SetAnimation(MARIO_ANI_FIRE_DROP);
        }
    }
}

void MarioDroppingState::HandleInput(CMario& mario, Input input)
{
    if (input == Input::PRESS_S && mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.state_ = MarioState::dropFly.GetInstance();
        mario.vy = -MARIO_DROP_FLY_SPEED_Y;
    }
    else  MarioJumpingState::HandleInput(mario, input);
}

void MarioDroppingState::Update(CMario& mario, DWORD dt)
{
    if (mario.isOnGround)
    {
        if (CGame::GetInstance()->GetCurrentScene()->isFinished)
        {
            mario.state_ = MarioState::walking.GetInstance();
        }
        else {
            mario.state_ = MarioState::standing.GetInstance();
        }
    }
    //DebugOut(L"Dropping\n");
}

void MarioDroppingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

