#include "MarioKickState.h"
#include "MarioStandingState.h"
#include "Mario.h"

MarioKickState* MarioKickState::__instance = NULL;

MarioKickState* MarioKickState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioKickState();
        DebugOut(L"Init MarioKickState\n");
    }
    return __instance;
}

void MarioKickState::HandleInput(CMario& mario, Input input)
{
    if (kickStartTime == 0)
    {
        MarioOnGroundState::HandleInput(mario, input);
    }
}

void MarioKickState::Enter(CMario& mario)
{
    if (mario.GetLevel() == MARIO_LEVEL_SMALL)
    {
        mario.SetAnimation(MARIO_ANI_SMALL_KICK);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_BIG_KICK);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_RACCOON_KICK);
    }
}

void MarioKickState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioKickState::Update(CMario& mario, DWORD dt)
{
    if (GetTickCount64() - kickStartTime > MARIO_KICK_TIME)
    {
        mario.state_ = MarioState::standing.GetInstance();
        kickStartTime = 0;
    }
    //DebugOut(L"Kick %d\n", GetTickCount64() - kick_time_start);
}