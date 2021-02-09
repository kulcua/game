#include "MarioStandingState.h"
#include "Utils.h"
#include "Mario.h"
#include "MarioState.h"

void MarioStandingState::HandleInput(CMario& mario)
{
  /*  mario.state_ = &MarioState::standing;*/
    //if (game->IsKeyDown())
    //{
    //    // Stand up...
    //}
    //else
    {
        // Didn't handle input, so walk up hierarchy.
        //MarioOnGroundState::HandleInput(mario);
    }
}

void MarioStandingState::Enter(CMario& mario)
{
    if (mario.GetLevel() == MARIO_LEVEL_SMALL)
    {
        mario.SetAnimation(MARIO_ANI_SMALL_IDLE);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_BIG_IDLE);
    }
}

void MarioStandingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}

void MarioStandingState::Update(CMario& mario)
{

}

void MarioStandingState::Render()
{

}
