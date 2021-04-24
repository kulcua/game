#include "MarioFlyingState.h"
#include "Mario.h"
#include "MarioDroppingState.h"

MarioFlyingState* MarioFlyingState::__instance = NULL;

MarioFlyingState* MarioFlyingState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioFlyingState();
    }
    return __instance;
}

void MarioFlyingState::HandleInput(CMario& mario, Input input)
{
    MarioJumpingState::HandleInput(mario, input);
    if (input == PRESS_S)
    {
        if (mario.GetPower() == MARIO_MAX_POWER && mario.GetLevel() == MARIO_LEVEL_RACCOON)
        {
            mario.vy = -MARIO_FLY_SPEED_Y;
        }
    }

}

void MarioFlyingState::Enter(CMario& mario) // declare (CMario& mario) means in CMario has a friend class MarioFlyingState
{
    if (mario.isHandleShell)
    {
        if (mario.GetLevel() == MARIO_LEVEL_SMALL)
        {
            mario.SetAnimation(MARIO_ANI_SMALL_HANDLESHELL_JUMP_DROP);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_BIG)
        {
            mario.SetAnimation(MARIO_ANI_BIG_HANDLESHELL_JUMP_DROP);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        {
            mario.SetAnimation(MARIO_ANI_RACCOON_HANDLESHELL_JUMP_FLY_DROP);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
        {
            mario.SetAnimation(MARIO_ANI_FIRE_HANDLESHELL_JUMP_DROP);
        }
    }
    else {
        if (mario.GetLevel() == MARIO_LEVEL_SMALL)
        {
            mario.SetAnimation(MARIO_ANI_SMALL_FLY);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_BIG)
        {
            mario.SetAnimation(MARIO_ANI_BIG_FLY);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        {
            mario.SetAnimation(MARIO_ANI_RACCOON_FLY);
        }
        else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
        {
            mario.SetAnimation(MARIO_ANI_FIRE_FLY);
        }
    }
}

void MarioFlyingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioFlyingState::Update(CMario& mario, DWORD dt)
{
    mario.isGrounded = false;

    if (mario.isPower == false)
    {
        mario.state_ = MarioState::dropping.GetInstance();
    }
}