#include "MarioTailHitState.h"
#include "Mario.h"
#include "MarioStandingState.h"

#define MARIO_HIT_TIME 210

MarioTailHitState* MarioTailHitState::__instance = NULL;

MarioTailHitState* MarioTailHitState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioTailHitState();
    }
    return __instance;
}

void MarioTailHitState::HandleInput(CMario& mario, Input input)
{
    if (input == RELEASE_A)
    {
        mario.PowerReset();
    }
}

void MarioTailHitState::Enter(CMario& mario)
{
    if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_RACCOON_SPIN);
    }
}

void MarioTailHitState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioTailHitState::Update(CMario& mario, DWORD dt)
{
    if (GetTickCount64() - hitStartTime > MARIO_HIT_TIME)
    {
        hitStartTime = 0;
        mario.state_ = MarioState::standing.GetInstance();
        mario.isAttack = false;
    }
    //DebugOut(L"MarioTailHitState\n");
}