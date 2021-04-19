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
        if (mario.isGrounded)
            mario.SetAnimation(MARIO_ANI_FIRE_SHOOT_FIREBALL_IDLE);
        else 
            mario.SetAnimation(MARIO_ANI_FIRE_SHOOT_FIREBALL_JUMP);
    }
}

void MarioShootFireBallState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioShootFireBallState::Update(CMario& mario, DWORD dt)
{
    if (GetTickCount64() - hitStartTime > MARIO_HIT_TIME)
    {
        hitStartTime = 0;
        mario.state_ = MarioState::standing.GetInstance();
    }
    //DebugOut(L"MarioShootFireBallState\n");
}