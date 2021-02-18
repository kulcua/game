#include "MarioDuckingState.h"
#include "MarioStandingState.h"
#include "Mario.h"

MarioDuckingState* MarioDuckingState::__instance = NULL;

MarioDuckingState* MarioDuckingState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioDuckingState();
        DebugOut(L"Init MarioDuckingState\n");
    }
    return __instance;
}

void MarioDuckingState::Enter(CMario& mario)
{
    if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_BIG_SIT);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_RACCOON_SIT);
    }
}

void MarioDuckingState::HandleInput(CMario& mario, Input input)
{
    MarioOnGroundState::HandleInput(mario, input);
}

void MarioDuckingState::Update(CMario& mario, DWORD dt)
{
    //DebugOut(L"MarioDuckingState\n");
}

void MarioDuckingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{  
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
    if (mario.isSit)
    {      
        bottom = mario.y + MARIO_SIT_BBOX_HEIGHT;
    }  
}

