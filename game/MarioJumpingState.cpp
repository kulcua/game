#include "MarioJumpingState.h"
#include "Mario.h"
#include "Game.h"
#include "MarioStandingState.h"
#include "MarioDroppingState.h"
#include "MarioTailHitState.h"

MarioJumpingState* MarioJumpingState::__instance = NULL;

MarioJumpingState* MarioJumpingState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioJumpingState();
        DebugOut(L"Init MarioJumpingState\n");
    }
    return __instance;
}

void MarioJumpingState::Enter(CMario& mario)
{
    if (mario.GetLevel() == MARIO_LEVEL_SMALL)
    {
        mario.SetAnimation(MARIO_ANI_SMALL_JUMP);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_BIG_JUMP);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_RACCOON_JUMP);
    }
}

void MarioJumpingState::HandleInput(CMario& mario, Input input)
{
    CGame* game = CGame::GetInstance();
    if (input == KEY_STATE)
    {
        if (game->IsKeyDown(DIK_RIGHT))
        {
            mario.nx = 1;
            mario.vx = MARIO_WALKING_SPEED;
        }
        else if (game->IsKeyDown(DIK_LEFT))
        {
            mario.nx = -1;
            mario.vx = -MARIO_WALKING_SPEED;
        }
    }
    else if (input == RELEASE_A)
    {
        mario.PowerReset();

    }
    else if (input == RELEASE_S)
    {
        mario.highJump = false;
    }
    else if (input == PRESS_A)
    {
        if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        {
            mario.isAttack = true;
            mario.state_ = MarioState::tailHit.GetInstance();
            MarioState::tailHit.GetInstance()->StartHit();
        }
    }
}

void MarioJumpingState::Update(CMario& mario, DWORD dt)
{ 
    if (mario.isGrounded == false && mario.vy > 0 && mario.GetPower() < 6)
        mario.state_ = MarioState::dropping.GetInstance();
    else if (mario.isGrounded) // if mario suddenly get on Ground
        mario.state_ = MarioState::standing.GetInstance();

    //region check highJump
    if (mario.highJump)
    {
        if (GetTickCount64() - jump_time_start > MARIO_HIGH_JUMP_TIME)
        {
            jump_time_start = 0;
        }
        else
        {
            mario.vy = -MARIO_JUMP_SPEED_Y;
        }   
    }
    //DebugOut(L"Jumping %f\n", mario.vx);
}

void MarioJumpingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioJumpingState::StartJump()
{
    jump_time_start = GetTickCount64();
}

