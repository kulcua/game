#include "MarioRunningState.h"
#include "Mario.h"

MarioRunningState* MarioRunningState::__instance = NULL;

MarioRunningState* MarioRunningState::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new MarioRunningState();
	}
	return __instance;
}

void MarioRunningState::Enter(CMario& mario)
{
	if (mario.isHandleShell)
	{
		if (mario.GetLevel() == MARIO_LEVEL_SMALL)
		{
			mario.SetAnimation(MARIO_ANI_SMALL_HANDLESHELL_RUN);
		}
		else if (mario.GetLevel() == MARIO_LEVEL_BIG)
		{
			mario.SetAnimation(MARIO_ANI_BIG_HANDLESHELL_RUN);
		}
		else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
		{
			mario.SetAnimation(MARIO_ANI_RACCOON_HANDLESHELL_RUN);
		}
		else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
		{
			mario.SetAnimation(MARIO_ANI_FIRE_HANDLESHELL_RUN);
		}
	}
	else
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
		else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
		{
			mario.SetAnimation(MARIO_ANI_FIRE_RUN);
		}
	}
}

void MarioRunningState::HandleInput(CMario& mario, Input input)
{
	MarioOnGroundState::HandleInput(mario, input);
}

void MarioRunningState::Update(CMario& mario, DWORD dt)
{
	MarioState::Update(mario, dt);
	//DebugOut(L"Running\n");
}

void MarioRunningState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
	MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

