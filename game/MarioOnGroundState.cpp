#include "MarioOnGroundState.h"
#include <dinput.h>
#include "Utils.h"
//#include "MarioJumpingState.h"
//#include "MarioDuckingState.h"

void MarioOnGroundState::HandleInput(CMario& mario)
{
   /* CGame* game = CGame::GetInstance();*/
    if (game->IsKeyDown(DIK_S))
    {
        DebugOut(L"jumping \n");
        //return new MarioJumpingState();  
    }
    else if (game->IsKeyDown(DIK_DOWN))
    {
        DebugOut(L"ducking \n");
        //return new MarioDuckingState();
    }
    //return NULL;
}