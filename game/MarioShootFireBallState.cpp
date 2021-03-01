#include "MarioShootFireBallState.h"
#include "Mario.h"
#include "MarioStandingState.h"

#define MARIO_HIT_TIME 100

MarioShootFireBallState* MarioShootFireBallState::__instance = NULL;

MarioShootFireBallState* MarioShootFireBallState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioShootFireBallState();
        DebugOut(L"Init MarioShootFireBallState\n");
    }
    return __instance;
}

void MarioShootFireBallState::HandleInput(CMario& mario, Input input)
{
    if (input == RELEASE_A)
    {
        mario.PowerReset();
    }
}

void MarioShootFireBallState::Enter(CMario& mario) // declare (CMario& mario) means in CMario has a friend class MarioShootFireBallState
{
    if (mario.GetLevel() == MARIO_LEVEL_FIRE)
    {
        mario.SetAnimation(MARIO_ANI_FIRE_SHOOT_FIREBALL);
    }
}

void MarioShootFireBallState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioShootFireBallState::Update(CMario& mario, DWORD dt)
{
    if (GetTickCount64() - hit_time_start > MARIO_HIT_TIME)
    {
        hit_time_start = 0;
        mario.state_ = MarioState::standing.GetInstance();
        mario.isAttack = false;
    }
    //DebugOut(L"MarioShootFireBallState\n");
}