#include "MarioOnGroundState.h"
#include "Mario.h"
#include "Game.h"
#include "MarioJumpingState.h"
#include "MarioWalkingState.h"
#include "MarioStandingState.h"
#include "MarioDuckingState.h"
#include "MarioRunningState.h"
#include "MarioStoppingState.h"
#include "MarioPreFlyState.h"
#include "MarioFlyingState.h"
#include "MarioTailHitState.h"
#include "MarioShootFireBallState.h"

void SwitchSittingToWalking(CMario& mario)
{
    mario.isSit = false;
    if (mario.GetLevel() == MARIO_LEVEL_BIG || mario.GetLevel() == MARIO_LEVEL_FIRE)
        mario.y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        mario.y -= MARIO_RACCOON_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
}

void SetPositionGetInSitState(CMario& mario)
{
    if (mario.GetLevel() != MARIO_LEVEL_SMALL)
    {
        mario.isSit = true;
        if (mario.GetLevel() == MARIO_LEVEL_BIG || mario.GetLevel() == MARIO_LEVEL_FIRE)
            mario.y += MARIO_BIG_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
            mario.y += MARIO_RACCOON_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
    }
}

void SetPositionGetOutSitState(CMario& mario)
{
    if (mario.GetLevel() != MARIO_LEVEL_SMALL)
    {
        mario.isSit = false;
        if (mario.GetLevel() == MARIO_LEVEL_BIG || mario.GetLevel() == MARIO_LEVEL_FIRE)
            mario.y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
            mario.y -= MARIO_RACCOON_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
    }
}

void SetStateWalk_Run_PreFly(CMario &mario)
{
    if (mario.isGrounded) {
        if (mario.isPower)
        {
            if (mario.GetPower() < MARIO_MAX_POWER)
            {
                mario.vx = mario.nx * MARIO_RUN_SPEED;
                mario.state_ = MarioState::running.GetInstance();
            }
            else if (mario.GetPower() == MARIO_MAX_POWER)
            {
                mario.vx = mario.nx * MARIO_RUN_SPEED;
                mario.state_ = MarioState::preFly.GetInstance();
            }
        }
        else
        {
            mario.vx = mario.nx * MARIO_WALKING_SPEED;
            mario.state_ = MarioState::walking.GetInstance();
        }
    }
}

void SetStopStateWhenHandleShell(CMario& mario)
{
    mario.PowerReset();
    if (mario.isHandleShell == false)
        mario.state_ = MarioState::stopping.GetInstance();
    else {
        //if handleShell but stop -> still keep flag isPower
        mario.isPower = true;
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
            {
                SetStopStateWhenHandleShell(mario);
            }
            else SetStateWalk_Run_PreFly(mario);
        }
        else if (game->IsKeyDown(DIK_LEFT))
        {
            mario.nx = -1;

            if (mario.isSit) // if Mario is sitting
                SwitchSittingToWalking(mario);
            if (mario.vx > 0)
            {
                SetStopStateWhenHandleShell(mario);
            }
            else SetStateWalk_Run_PreFly(mario);
        }
    }
    
    if (input == PRESS_S)
    {
        if (mario.isGrounded) // check isGrounded to jump again
        {
            if (mario.GetPower() == MARIO_MAX_POWER)
            { // if can Fly
                if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
                {
                    mario.vy = -MARIO_FLY_SPEED_Y;
                }
                else
                {
                    mario.vy = -MARIO_JUMP_SPEED_Y;
                }
                mario.state_ = MarioState::flying.GetInstance();
            }
            else { // if not, Jump normally
                mario.isHighJump = true;
                if (mario.isSit == true) // if isSit, don't change state
                {
                    MarioState::ducking.GetInstance()->StartJump();
                }
                else {
                    mario.state_ = MarioState::jumping.GetInstance();
                    MarioState::jumping.GetInstance()->StartJump();
                }
                mario.vy = -MARIO_JUMP_SPEED_Y;
            }
            mario.isGrounded = false;
        }  
    }
    // Mario is walking can't duck
    // mario.vx == 0: prevent multiple key when walk and sit
    else if (input == PRESS_DOWN && mario.vx == 0)
    {
        mario.state_ = MarioState::ducking.GetInstance();
        SetPositionGetInSitState(mario);
    }
    else if (input == RELEASE_DOWN && mario.vx == 0)
    {
        mario.state_ = MarioState::standing.GetInstance();
        SetPositionGetOutSitState(mario);
    }
    else if (input == PRESS_A)
    {
        mario.isPower = true;
        if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        {
            mario.isAttack = true;
            mario.state_ = MarioState::tailHit.GetInstance();
            MarioState::tailHit.GetInstance()->StartHit();
        } 
        else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
        {
            mario.state_ = MarioState::shootFireball.GetInstance();
            MarioState::shootFireball.GetInstance()->StartHit();
            mario.pool_->Create()->Init(&mario);
        }
    }
    else if (input == RELEASE_A)
    {
        mario.PowerReset();
        mario.KickShell();
    }
    else if (input == RELEASE_LEFT || input == RELEASE_RIGHT)
    {
        mario.isPower = false;
    }
    else if (input == PRESS_LEFT || input == PRESS_RIGHT)
    {
        if (mario.isPower)
        {
            mario.PowerUp();
        }
    }
}
