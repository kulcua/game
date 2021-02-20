#include "MarioJumpingState.h"
#include "Mario.h"
#include "Game.h"
#include "MarioStandingState.h"
#include "MarioDroppingState.h"

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
}

void MarioJumpingState::Update(CMario& mario, DWORD dt)
{ 
    if (mario.isGrounded == false && mario.vy > 0 && mario.GetPower() < 6)
        mario.state_ = MarioState::dropping.GetInstance();
    else if (mario.isGrounded) // if mario suddenly get on Ground
        mario.state_ = MarioState::standing.GetInstance();
    //DebugOut(L"Jumping %f\n", mario.vx);
}

void MarioJumpingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

