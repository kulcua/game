#include "MarioDropFlyState.h"
#include "Mario.h"
#include "Game.h"

MarioDropFlyState* MarioDropFlyState::__instance = NULL;

MarioDropFlyState* MarioDropFlyState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioDropFlyState();
    }
    return __instance;
}

void MarioDropFlyState::Enter(CMario& mario)
{
    if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        if (mario.isHandleShell)
        {
            mario.SetAnimation(MARIO_ANI_RACCOON_HANDLESHELL_JUMP_FLY_DROP);
        }
        else
            mario.SetAnimation(MARIO_ANI_RACCOON_DROP_FLY);
    }
}

void MarioDropFlyState::HandleInput(CMario& mario, Input input)
{
    MarioDroppingState::HandleInput(mario, input);
}

void MarioDropFlyState::Update(CMario& mario, DWORD dt)
{
    MarioDroppingState::Update(mario, dt);
    //DebugOut(L"Drop-Fly %f\n", mario.vx);
}

void MarioDropFlyState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

