#include "MarioOnGroundState.h"
#include "Mario.h"
#include "MarioJumpingState.h"
#include "MarioWalkingState.h"
#include "MarioStandingState.h"
#include "MarioDuckingState.h"
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

void MarioOnGroundState::HandleInput(CMario& mario, Input input)
{
    if (input == KEY_STATE)
    {
        CGame* game = CGame::GetInstance();
        if (game->IsKeyDown(DIK_RIGHT))
        {
            //DebugOut(L"DIK_RIGHT\n");
            if (mario.isSit)
                SwitchSittingToWalking(mario);

            if (mario.isGrounded)
            {
                mario.state_ = MarioState::walking.GetInstance();
            }
            mario.nx = 1;
            mario.vx = MARIO_WALKING_SPEED;
        }
        else if (game->IsKeyDown(DIK_LEFT))
        {
            //DebugOut(L"DIK_LEFT\n");
            if (mario.isSit) // if Mario is sitting
                SwitchSittingToWalking(mario);
            
            if (mario.isGrounded)
            {
                mario.state_ = MarioState::walking.GetInstance();
            }
            mario.nx = -1;
            mario.vx = -MARIO_WALKING_SPEED;
        }
    }

    else if (input == PRESS_S)
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
}
