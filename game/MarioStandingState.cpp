#include "MarioStandingState.h"
#include "Utils.h"
#include "Mario.h"

MarioStandingState* MarioStandingState::__instance = NULL;

MarioStandingState* MarioStandingState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioStandingState();
        DebugOut(L"Init Standing State\n");
    }
	return __instance;
}

void MarioStandingState::HandleInput(CMario& mario)
{
    //mario.state_ = &MarioState::standing;
    //if (game->IsKeyDown())
    //{
    //    // Stand up...
    //}
    //else
    {
        // Didn't handle input, so walk up hierarchy.
        MarioOnGroundState::HandleInput(mario);
    }
    //return NULL;
}

void MarioStandingState::Enter(CMario& mario) // declare (CMario& mario) means in CMario has a friend class MarioStandingState
{
    if (mario.GetLevel() == MARIO_LEVEL_SMALL)
    {
        mario.SetAnimation(MARIO_ANI_SMALL_IDLE);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_BIG_IDLE);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_RACCOON_IDLE);
    }
}

void MarioStandingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}

void MarioStandingState::Update(CMario& mario)
{

}