#include "MarioOnGroundState.h"
#include <dinput.h>

MarioState* MarioOnGroundState::HandleInput(CMario& mario, int keyCode)
{
    if (keyCode == DIK_A)
    {
        mario.state_ = &MarioState::jumping;
    }
    else if (keyCode == DIK_DOWN)
    {
        mario.state_ = &MarioState::ducking;
    }
}

void MarioOnGroundState::Update(CMario& mario)
{

}

void MarioOnGroundState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}

void MarioOnGroundState::Render()
{

}