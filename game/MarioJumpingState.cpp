#include "MarioJumpingState.h"
#include "Mario.h"
#include "MarioStandingState.h"

MarioJumpingState* MarioJumpingState::__instance = NULL;

MarioJumpingState* MarioJumpingState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioJumpingState();
        DebugOut(L"Init MarioJumpingState\n");
    }
    return __instance;
}

void MarioJumpingState::Enter(CMario& mario)
{
    if (mario.GetLevel() == MARIO_LEVEL_SMALL)
    {
        mario.SetAnimation(MARIO_ANI_SMALL_JUMP);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_BIG_JUMP);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_RACCOON_JUMP);
    }
}

void MarioJumpingState::HandleInput(CMario& mario, Input input)
{

}

void MarioJumpingState::Update(CMario& mario)
{ 
    //DebugOut(L"Jumping\n");
}

void MarioJumpingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

