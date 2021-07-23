#include "MarioOnGroundState.h"
#include "Mario.h"
#include "Game.h"
#include "MarioJumpingState.h"
#include "MarioWalkingState.h"
#include "MarioStandingState.h"
#include "MarioSittingState.h"
#include "MarioRunningState.h"
#include "MarioStoppingState.h"
#include "MarioPreFlyState.h"
#include "MarioFlyingState.h"
#include "MarioTailHitState.h"
#include "MarioShootFireBallState.h"

void SetPositionGetInSitState(CMario& mario)
{
    if (mario.GetLevel() != MARIO_LEVEL_SMALL)
    {
        mario.state_ = MarioState::sitting.GetInstance();
        MarioSittingState::GetInstance()->isSit = true;
        if (mario.GetLevel() == MARIO_LEVEL_BIG || mario.GetLevel() == MARIO_LEVEL_FIRE)
            mario.y += MARIO_BIG_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
            mario.y += MARIO_RACCOON_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
    }
}

void SetStateWalk_Run_PreFly(CMario &mario)
{
    if (mario.isOnGround && mario.state_ != MarioState::tailHit.GetInstance()) {
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
    if (input == Input::KEY_STATE)
    {
        if (game->IsKeyDown(DIK_RIGHT))
        {
            mario.nx = 1;
            if (mario.vx < 0)
            {
                SetStopStateWhenHandleShell(mario);
            }
            else SetStateWalk_Run_PreFly(mario);
        }
        else if (game->IsKeyDown(DIK_LEFT))
        {
            mario.nx = -1;
            if (mario.vx > 0)
            {
                SetStopStateWhenHandleShell(mario);
            }
            else SetStateWalk_Run_PreFly(mario);
        }
    }
    
    if (input == Input::PRESS_S)
    {
        if (mario.isOnGround) // check isOnGround to jump again
        {
            MarioJumpingState::GetInstance()->isHighJump = true;
            if (MarioSittingState::GetInstance()->isSit) // if isSit, don't change state
            {
                MarioState::sitting.GetInstance()->StartJump();
            }
            else {
                mario.state_ = MarioState::jumping.GetInstance();
                MarioState::jumping.GetInstance()->StartJump();
            }
            mario.vy = -MARIO_JUMP_SPEED_Y;
            mario.isOnGround = false;
        }  
    }
    // Mario is walking can't duck
    // mario.vx == 0: prevent multiple key when walk and sit
    else if (input == Input::PRESS_DOWN)
    {
        if (mario.vx == 0)
            SetPositionGetInSitState(mario);
    }
    else if (input == Input::PRESS_A)
    {
        mario.isPower = true;
        if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
        {
            mario.state_ = MarioState::tailHit.GetInstance();
            MarioState::tailHit.GetInstance()->tailHitting = true;
            MarioState::tailHit.GetInstance()->StartHit();
        } 
        else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
        {
            CFireBall* fireBall = FireBallPool::GetInstance()->Create();
            if (fireBall != NULL)
            {
                mario.state_ = MarioState::shootFireball.GetInstance();
                MarioState::shootFireball.GetInstance()->StartHit();
                fireBall->InitForMario();
            }
        }
    }
    else if (input == Input::RELEASE_A)
    {
        mario.PowerReset();
        if (mario.isHandleShell)
            mario.KickShellAfterHandle();
    }
    else if (input == Input::RELEASE_LEFT || input == Input::RELEASE_RIGHT)
    {
        mario.PowerReset();
    }
    else if (input == Input::PRESS_LEFT || input == Input::PRESS_RIGHT)
    {
        if (mario.isPower)
        {
            mario.PowerUp();
        }
    }
}
