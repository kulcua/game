#include "MarioOnGroundState.h"
#include <dinput.h>

MarioState* MarioOnGroundState::HandleInput(CMario& mario)
{
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