#include "MarioSittingState.h"
#include "MarioStandingState.h"
#include "MarioJumpingState.h"
#include "Mario.h"
#include "Game.h"

MarioSittingState* MarioSittingState::__instance = NULL;

MarioSittingState* MarioSittingState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioSittingState();
    }
    return __instance;
}

void MarioSittingState::Enter(CMario& mario)
{
    if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_BIG_SIT);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_RACCOON_SIT);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
    {
        mario.SetAnimation(MARIO_ANI_FIRE_SIT);
    }
}

void SetPositionGetOutSitState(CMario& mario)
{
    MarioSittingState::GetInstance()->isSit = false;
    if (mario.GetLevel() == MARIO_LEVEL_BIG || mario.GetLevel() == MARIO_LEVEL_FIRE)
        mario.y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        mario.y -= MARIO_RACCOON_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
}

void MarioSittingState::HandleInput(CMario& mario, Input input)
{
    CGame* game = CGame::GetInstance();
    MarioOnGroundState::HandleInput(mario, input);
    if (input == Input::KEY_STATE)
    {
        if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))
        {
            SetPositionGetOutSitState(mario);
        }
    }
    if (input == Input::RELEASE_S)
    {
        MarioJumpingState::GetInstance()->isHighJump = false;
    }
    else if (input == Input::RELEASE_DOWN && mario.vx == 0)
    {
        mario.state_ = MarioState::standing.GetInstance();
        SetPositionGetOutSitState(mario);
    }
}

void MarioSittingState::Update(CMario& mario, DWORD dt)
{
    if (MarioJumpingState::GetInstance()->isHighJump)
    {
        if (GetTickCount64() - jumpStartTime > MARIO_HIGH_JUMP_TIME)
        {
            jumpStartTime = 0;
        }
        else
        {
            mario.vy = -MARIO_JUMP_SPEED_Y;
        }
    }
    //DebugOut(L"MarioSittingState\n");
}

void MarioSittingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{  
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
    bottom = mario.y + MARIO_SIT_BBOX_HEIGHT;
}

void MarioSittingState::StartJump()
{
    jumpStartTime = GetTickCount64();
}

