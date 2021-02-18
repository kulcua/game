#include "MarioWalkingState.h"
#include "MarioStandingState.h"
#include "Mario.h"

MarioWalkingState* MarioWalkingState::__instance = NULL;

MarioWalkingState* MarioWalkingState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioWalkingState();
        DebugOut(L"Init MarioWalkingState\n");
    }
    return __instance;
}

void MarioWalkingState::Enter(CMario& mario)
{
    if (mario.GetLevel() == MARIO_LEVEL_SMALL)
    {
        mario.SetAnimation(MARIO_ANI_SMALL_WALKING);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_BIG_WALKING);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_RACCOON_WALKING);
    }
}

void MarioWalkingState::HandleInput(CMario& mario, Input input)
{
    MarioOnGroundState::HandleInput(mario, input);
}

void MarioWalkingState::Update(CMario& mario, DWORD dt)
{
	//if (mario.vx == 0)
	//	//&&state != MARIO_STATE_DIE)
	//{
	//	mario.state_ = MarioState::standing.GetInstance();
	//}
	//else {
	//	//DebugOut(L"vx: %f\n", vx);
	//	if (mario.vx > 0)
	//	{
	//		a = -MARIO_ACCELERATION;
	//		mario.vx += a * dt;
	//		if (mario.vx < 0)
	//			mario.vx = 0;
	//	}
	//	else
	//	{
	//		a = MARIO_ACCELERATION;
	//		mario.vx += a * dt;
	//		if (mario.vx > 0)
	//			mario.vx = 0;
	//	}
	//}
    //DebugOut(L"Walking\n");
}

void MarioWalkingState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

