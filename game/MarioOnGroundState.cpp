#include "MarioOnGroundState.h"
#include "Mario.h"
#include "MarioJumpingState.h"
#include "MarioWalkingState.h"
#include "MarioStandingState.h"
#include "MarioDuckingState.h"
#include "MarioRunningState.h"
#include "MarioStoppingState.h"
#include "Game.h"

void SwitchSittingToWalking(CMario& mario)
{
    mario.isSit = false;
    if (mario.GetLevel() == MARIO_LEVEL_BIG)
        mario.y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        mario.y -= MARIO_RACCOON_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
}

void SettingLocationGetInSitState(CMario& mario)
{
    if (mario.GetLevel() != MARIO_LEVEL_SMALL)
    {
        mario.isSit = true;
        if (mario.GetLevel() == MARIO_LEVEL_BIG)
            mario.y += MARIO_BIG_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
            mario.y += MARIO_RACCOON_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
    }
}

void SettingLocationGetOutSitState(CMario& mario)
{
    if (mario.GetLevel() != MARIO_LEVEL_SMALL)
    {
        mario.isSit = false;
        if (mario.GetLevel() == MARIO_LEVEL_BIG)
            mario.y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
            mario.y -= MARIO_RACCOON_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
    }
}

void SetStateWalkOrRun(CMario &mario)
{
    if (mario.isGrounded) {
        if (mario.isRun)
        {
            mario.vx = mario.nx * MARIO_RUN_SPEED;
            mario.state_ = MarioState::running.GetInstance();
        }
        else {
            mario.vx = mario.nx * MARIO_WALKING_SPEED;
            mario.state_ = MarioState::walking.GetInstance();
        }
    }
}

void MarioOnGroundState::HandleInput(CMario& mario, Input input)
{
    CGame* game = CGame::GetInstance();
    if (input == KEY_STATE)
    {
        if (game->IsKeyDown(DIK_RIGHT))
        {
            mario.nx = 1;

            if (mario.isSit)
                SwitchSittingToWalking(mario);
            if (mario.vx < 0)
                mario.state_ = MarioState::stopping.GetInstance();
            else SetStateWalkOrRun(mario);
        }
        else if (game->IsKeyDown(DIK_LEFT))
        {
            mario.nx = -1;

            if (mario.isSit) // if Mario is sitting
                SwitchSittingToWalking(mario);
            if (mario.vx > 0)
                mario.state_ = MarioState::stopping.GetInstance();
            else SetStateWalkOrRun(mario);
        }
    }
    
    if (input == PRESS_S)
    {
        if (mario.isGrounded) // check isGrounded to jump again
        {
            if (mario.isSit == false) // if isSit, don't change state
            {
                mario.state_ = MarioState::jumping.GetInstance();
            }
            mario.vy = -MARIO_JUMP_SPEED_Y;
            mario.isGrounded = false;
        }
    }
    // Mario is walking can't duck
    // mario.vx == 0: prevent multiple key when walk and sit
    else if (input == PRESS_DOWN && mario.vx == 0)
    {
        mario.state_ = MarioState::ducking.GetInstance();
        SettingLocationGetInSitState(mario);
    }
    else if (input == RELEASE_DOWN && mario.vx == 0)
    {
        mario.state_ = MarioState::standing.GetInstance();
        SettingLocationGetOutSitState(mario);
    }
    else if (input == PRESS_A)
    {
        mario.isRun = true;
    }
    else if (input == RELEASE_A)
    {
        mario.isRun = false;
    }
}
