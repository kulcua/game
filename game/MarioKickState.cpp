#include "MarioKickState.h"
#include "MarioStandingState.h"
#include "Mario.h"

MarioKickState* MarioKickState::__instance = NULL;

MarioKickState* MarioKickState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioKickState();
    }
    return __instance;
}

void MarioKickState::HandleInput(CMario& mario, Input input)
{

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
    else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
    {
        mario.SetAnimation(MARIO_ANI_FIRE_KICK);
    }
}

void MarioKickState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioKickState::Update(CMario& mario, DWORD dt)
{
    mario.vx = 0;
    if (GetTickCount64() - kickStartTime > MARIO_KICK_TIME)
    {
        mario.state_ = MarioState::standing.GetInstance();
        kickStartTime = 0;
    }
}