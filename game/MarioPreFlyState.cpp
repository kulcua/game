#include "MarioPreFlyState.h"
#include "MarioFlyingState.h"
#include "Mario.h"

MarioPreFlyState* MarioPreFlyState::__instance = NULL;

MarioPreFlyState* MarioPreFlyState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioPreFlyState();
    }
    return __instance;
}

void MarioPreFlyState::HandleInput(CMario& mario, Input input)
{
    MarioOnGroundState::HandleInput(mario, input);

    if (input == PRESS_S)
    {
        if (mario.GetPower() == MARIO_MAX_POWER)
        { // if can Fly
            if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
            {
                mario.vy = -MARIO_FLY_SPEED_Y;
            }
            else
            {
                mario.vy = -MARIO_JUMP_FLY_SPEED_Y;
            }
            mario.state_ = MarioState::flying.GetInstance();
            mario.isGrounded = false;
        }
    }
}

void MarioPreFlyState::Enter(CMario& mario)
{
    if (mario.isHandleShell)
    {
        if (mario.GetLevel() == MARIO_LEVEL_SMALL)
        {
            mario.SetAnimation(MARIO_ANI_SMALL_HANDLESHELL_RUN);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_BIG)
        {
            mario.SetAnimation(MARIO_ANI_BIG_HANDLESHELL_RUN);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        {
            mario.SetAnimation(MARIO_ANI_RACCOON_HANDLESHELL_RUN);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
        {
            mario.SetAnimation(MARIO_ANI_FIRE_HANDLESHELL_RUN);
        }
    }
    else
    {
        if (mario.GetLevel() == MARIO_LEVEL_SMALL)
        {
            mario.SetAnimation(MARIO_ANI_SMALL_PRE_FLY);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_BIG)
        {
            mario.SetAnimation(MARIO_ANI_BIG_PRE_FLY);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        {
            mario.SetAnimation(MARIO_ANI_RACCOON_PRE_FLY);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
        {
            mario.SetAnimation(MARIO_ANI_FIRE_PRE_FLY);
        }
    }
}

void MarioPreFlyState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioPreFlyState::Update(CMario& mario, DWORD dt)
{
    MarioState::Update(mario, dt);
    //DebugOut(L"PreFly\n");
}