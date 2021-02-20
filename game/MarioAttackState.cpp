#include "MarioAttackState.h"
#include "Mario.h"
#include "MarioTailHitState.h"

MarioAttackState* MarioAttackState::__instance = NULL;

MarioAttackState* MarioAttackState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioAttackState();
        DebugOut(L"Init MarioAttackState\n");
    }
    return __instance;
}

void MarioAttackState::HandleInput(CMario& mario, Input input)
{

}

void MarioAttackState::Enter(CMario& mario) // declare (CMario& mario) means in CMario has a friend class MarioAttackState
{

}

void MarioAttackState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioAttackState::Update(CMario& mario, DWORD dt)
{

}