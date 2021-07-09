#include "MarioLevelDownState.h"
#include "Mario.h"
#include "MarioStandingState.h"

MarioLevelDownState* MarioLevelDownState::__instance = NULL;

MarioLevelDownState* MarioLevelDownState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioLevelDownState();
    }
    return __instance;
}

void MarioLevelDownState::HandleInput(CMario& mario, Input input)
{

}

void MarioLevelDownState::Enter(CMario& mario)
{
    if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_ITEM_SMALL_TO_BIG);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_ITEM_BIG_TO_RACOON);
    }
}

void MarioLevelDownState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioLevelDownState::Update(CMario& mario, DWORD dt)
{
    if (GetTickCount64() - levelDownStartTime > MARIO_LEVEL_UP_TIME)
    {
        levelDownStartTime = 0;
        mario.SetLevel(mario.GetLevel() - 1);

        mario.state_ = MarioState::standing.GetInstance();
    }
    //DebugOut(L"MarioLevelDownState\n");
}

void MarioLevelDownState::StartLevelDown()
{
    levelDownStartTime = GetTickCount64();
}