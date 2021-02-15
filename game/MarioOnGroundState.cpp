#include "MarioOnGroundState.h"
#include "Utils.h"
#include "Game.h"
#include "MarioJumpingState.h"
#include "MarioWalkingState.h"
#include "MarioStandingState.h"

void MarioOnGroundState::HandleInput(CMario& mario)
{
    CGame* game = CGame::GetInstance();
    if (game->IsKeyDown(DIK_S))
    {
        if (mario.isGrounded) // check isGrounded to jump again
        {
            //DebugOut(L"jumping \n");
            mario.state_ = MarioState::jumping.GetInstance();   
            mario.vy = -MARIO_JUMP_SPEED_Y;
        }
        mario.isGrounded = false;
    }
    else if (game->IsKeyDown(DIK_LEFT))
    {
        //DebugOut(L"left\n");
        if (mario.isGrounded)
        {
            mario.state_ = MarioState::walking.GetInstance();
        }
        
        mario.nx = -1;
        mario.vx = -MARIO_WALKING_SPEED;
    }
    else if (game->IsKeyDown(DIK_RIGHT))
    {
        //DebugOut(L"right\n");
        if (mario.isGrounded) 
            //&& mario.vx > 0)
        {
            mario.state_ = MarioState::walking.GetInstance();
        }

        mario.nx = 1;
        mario.vx = MARIO_WALKING_SPEED;
    }
    else 
        //if (mario.isGrounded)
    {
        mario.state_ = MarioState::standing.GetInstance();
    }
}