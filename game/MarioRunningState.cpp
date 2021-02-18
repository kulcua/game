#include "MarioRunningState.h"
#include "Mario.h"

MarioRunningState* MarioRunningState::__instance = NULL;

MarioRunningState* MarioRunningState::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new MarioRunningState();
		DebugOut(L"Init MarioRunningState\n");
	}
	return __instance;
}

void MarioRunningState::Enter(CMario& mario)
{
	if (mario.GetLevel() == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_RUN);
	}
	else if (mario.GetLevel() == MARIO_LEVEL_BIG)
	{
		mario.SetAnimation(MARIO_ANI_BIG_RUN);
	}
	else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
	{
		mario.SetAnimation(MARIO_ANI_RACCOON_RUN);
	}
}

void MarioRunningState::HandleInput(CMario& mario, Input input)
{
	MarioOnGroundState::HandleInput(mario, input);
}

void MarioRunningState::Update(CMario& mario, DWORD dt)
{
	//DebugOut(L"Running\n");
}

void MarioRunningState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
	MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

