#include "MarioPreFlyState.h"
#include "Mario.h"

MarioPreFlyState* MarioPreFlyState::__instance = NULL;

MarioPreFlyState* MarioPreFlyState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioPreFlyState();
        DebugOut(L"Init MarioPreFlyState\n");
    }
    return __instance;
}

void MarioPreFlyState::HandleInput(CMario& mario, Input input)
{
    MarioOnGroundState::HandleInput(mario, input);
}

void MarioPreFlyState::Enter(CMario& mario) // declare (CMario& mario) means in CMario has a friend class MarioPreFlyState
{
    if (mario.GetLevel() == MARIO_LEVEL_SMALL)
    {
        mario.SetAnimation(MARIO_ANI_SMALL_PRE_FLY);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_BIG_PRE_FLY);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_RACCOON_PRE_FLY);
    }
}

void MarioPreFlyState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioPreFlyState::Update(CMario& mario, DWORD dt)
{
    //DebugOut(L"Running\n");
}