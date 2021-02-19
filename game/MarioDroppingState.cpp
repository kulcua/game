#include "MarioDroppingState.h"
#include "Mario.h"
#include "Game.h"
#include "MarioStandingState.h"
#include "MarioDropFlyState.h"

MarioDroppingState* MarioDroppingState::__instance = NULL;

MarioDroppingState* MarioDroppingState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioDroppingState();
        DebugOut(L"Init MarioDroppingState\n");
    }
    return __instance;
}

void MarioDroppingState::Enter(CMario& mario)
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
}

void MarioDroppingState::HandleInput(CMario& mario, Input input)
{
    MarioJumpingState::HandleInput(mario, input);
    if (input == PRESS_S && mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.state_ = MarioState::dropFly.GetInstance();
        mario.vy = -MARIO_DROP_FLY_SPEED_Y;
    }
}

void MarioDroppingState::Update(CMario& mario, DWORD dt)
{
    if (mario.isGrounded)
        mario.state_ = MarioState::standing.GetInstance();
    //DebugOut(L"Dropping %f\n", mario.vx);
}

void MarioDroppingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

