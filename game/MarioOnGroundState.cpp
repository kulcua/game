#include "MarioOnGroundState.h"
#include "Utils.h"
#include "Mario.h"
#include "MarioJumpingState.h"
#include "MarioWalkingState.h"
#include "MarioStandingState.h"
#include "MarioDuckingState.h"
#include "Game.h"

void MarioOnGroundState::HandleInput(CMario& mario, Input input)
{
    //DebugOut(L"input %d\n", input);
    if (input == KEY_STATE)
    {
        CGame* game = CGame::GetInstance();
        if (game->IsKeyDown(DIK_RIGHT))
        {
            if (mario.isSit) //tat isSit neu dang ngoi
            {
                mario.isSit = false;
                if (mario.GetLevel() == MARIO_LEVEL_BIG)
                    mario.y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
                else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
                    mario.y -= MARIO_RACCOON_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
            }

            if (mario.isGrounded)
            {
                mario.state_ = MarioState::walking.GetInstance();
            }
            mario.nx = 1;
            mario.vx = MARIO_WALKING_SPEED;
        }
        else if (game->IsKeyDown(DIK_LEFT))
        {
            if (mario.isSit) //tat isSit neu dang ngoi
    	    {
    		    mario.isSit = false;
    		    if (mario.GetLevel() == MARIO_LEVEL_BIG)
    			    mario.y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
    		    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    			    mario.y -= MARIO_RACCOON_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
    	    }

            if (mario.isGrounded)
            {
                mario.state_ = MarioState::walking.GetInstance();
            }
            mario.nx = -1;
            mario.vx = -MARIO_WALKING_SPEED;
        }
        else if (game->IsKeyDown(DIK_DOWN))
        {
            mario.state_ = MarioState::ducking.GetInstance();
        }
    }

    if (input == PRESS_S)
    {
        if (mario.isGrounded) // check isGrounded to jump again
        {
            mario.state_ = MarioState::jumping.GetInstance();
            mario.vy = -MARIO_JUMP_SPEED_Y;
            mario.isGrounded = false;
        }   
    }
    // mario is walking can't duck
    else if (input == PRESS_DOWN && mario.vx == 0)
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
    else if (input == RELEASE_DOWN && mario.vx == 0)
    {
        mario.isSit = false;
        if (mario.GetLevel() == MARIO_LEVEL_BIG)
            mario.y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
        else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
            mario.y -= MARIO_RACCOON_BBOX_HEIGHT - MARIO_SIT_BBOX_HEIGHT;
    }
}