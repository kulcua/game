#include "MarioWalkingState.h"
#include "MarioStandingState.h"
#include "MarioDroppingState.h"
#include "Mario.h"
#include "Game.h"

MarioWalkingState* MarioWalkingState::__instance = NULL;

MarioWalkingState* MarioWalkingState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioWalkingState();
    }
    return __instance;
}

void MarioWalkingState::Enter(CMario& mario)
{
    if (mario.isHandleShell)
    {
        if (mario.GetLevel() == MARIO_LEVEL_SMALL)
        {
            mario.SetAnimation(MARIO_ANI_SMALL_HANDLESHELL_RUN);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_BIG)
        {
            mario.SetAnimation(MARIO_ANI_BIG_HANDLESHELL_RUN);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        {
            mario.SetAnimation(MARIO_ANI_RACCOON_HANDLESHELL_RUN);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
        {
            mario.SetAnimation(MARIO_ANI_FIRE_HANDLESHELL_RUN);
        }
    }
    else
    {
        if (mario.GetLevel() == MARIO_LEVEL_SMALL)
        {
            mario.SetAnimation(MARIO_ANI_SMALL_WALK);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_BIG)
        {
            mario.SetAnimation(MARIO_ANI_BIG_WALK);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        {
            mario.SetAnimation(MARIO_ANI_RACCOON_WALK);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
        {
            mario.SetAnimation(MARIO_ANI_FIRE_WALK);
        }
    }  
}

void MarioWalkingState::HandleInput(CMario& mario, Input input)
{
    MarioOnGroundState::HandleInput(mario, input);
    if (input == Input::PRESS_A)
    {
        mario.isPower = true;
        mario.PowerUp();
    }
}

void MarioWalkingState::Update(CMario& mario, DWORD dt)
{
    MarioState::Update(mario, dt);
    if (CGame::GetInstance()->GetCurrentScene()->isFinished)
    {
        mario.vx = MARIO_WALKING_SPEED;
    }
    else if (mario.vy > MARIO_VY_DROP)
    {
        mario.isOnGround = false;
        mario.state_ = MarioState::dropping.GetInstance();
    }
    //DebugOut(L"Walking %d\n", mario.isOnGround);
}

void MarioWalkingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

