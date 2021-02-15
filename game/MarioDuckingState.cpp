#include "MarioDuckingState.h"
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

void MarioDuckingState::HandleInput(CMario& mario)
{
    MarioOnGroundState::HandleInput(mario);
}

void MarioDuckingState::Update(CMario& mario)
{

}

void MarioDuckingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    DebugOut(L"voooooooo\n");
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
    DebugOut(L"bottom: %f\n", bottom);
	bottom = mario.y + MARIO_SIT_BBOX_HEIGHT;
    DebugOut(L"bottom: %f\n", bottom);
}

