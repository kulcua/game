#include "MarioLevelUpState.h"
#include "Mario.h"
#include "MarioStandingState.h"

MarioLevelUpState* MarioLevelUpState::__instance = NULL;

MarioLevelUpState* MarioLevelUpState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioLevelUpState();
    }
    return __instance;
}

void MarioLevelUpState::HandleInput(CMario& mario, Input input)
{

}

void MarioLevelUpState::Enter(CMario& mario) // declare (CMario& mario) means in CMario has a friend class MarioLevelUpState
{
    if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_ITEM_SMALL_TO_BIG);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_ITEM_BOOM);
    }
}

void MarioLevelUpState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioLevelUpState::Update(CMario& mario, DWORD dt)
{
    if (GetTickCount64() - levelUpStartTime > MARIO_LEVEL_UP_TIME)
    {
        levelUpStartTime = 0;
        mario.state_ = MarioState::standing.GetInstance();
    }
    //DebugOut(L"MarioLevelUpState\n");
}