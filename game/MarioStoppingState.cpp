#include "MarioStoppingState.h"
#include "Mario.h"

MarioStoppingState* MarioStoppingState::__instance = NULL;

MarioStoppingState* MarioStoppingState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioStoppingState();
        DebugOut(L"Init MarioStoppingState\n");
    }
    return __instance;
}

void MarioStoppingState::Enter(CMario& mario)
{
    if (mario.GetLevel() == MARIO_LEVEL_SMALL)
    {
        mario.SetAnimation(MARIO_ANI_SMALL_STOP);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_BIG_STOP);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_RACCOON_STOP);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
    {
        mario.SetAnimation(MARIO_ANI_FIRE_STOP);
    }
}

void MarioStoppingState::HandleInput(CMario& mario, Input input)
{
    MarioOnGroundState::HandleInput(mario, input);
}

void MarioStoppingState::Update(CMario& mario, DWORD dt)
{
    MarioState::Update(mario, dt);
    //DebugOut(L"Stoping\n");
}

void MarioStoppingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

