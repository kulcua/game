#include "MarioOnGroundState.h"
#include <dinput.h>
#include "Utils.h"
#include "Game.h"

void MarioOnGroundState::HandleInput(CMario& mario)
{
    CGame* game = CGame::GetInstance();
    if (game->IsKeyDown(DIK_A))
    {
        //mario.state_ = &MarioState::jumping;
        DebugOut(L"jumping \n");
    }
    else if (game->IsKeyDown(DIK_DOWN))
    {
        DebugOut(L"ducking \n");
       /* mario.state_ = &MarioState::ducking;*/
    }
}