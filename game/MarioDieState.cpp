#include "MarioDieState.h"
#include "MarioDieState.h"
#include "Mario.h"
#include "Game.h"
#define WORLD_MAP_SCENE 2
#define MARIO_TIME_DIE 2000

MarioDieState* MarioDieState::__instance = NULL;

MarioDieState* MarioDieState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioDieState();
    }
    return __instance;
}

void MarioDieState::HandleInput(CMario& mario, Input input)
{

}

void MarioDieState::Enter(CMario& mario)
{
    mario.SetAnimation(MARIO_ANI_DIE);
}

void MarioDieState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
    right = left + MARIO_WIDTH;
    bottom = top + MARIO_HEIGHT;
}

void MarioDieState::Update(CMario& mario, DWORD dt)
{
    mario.y += mario.dy;

    if (dieTimeStart > 0 && GetTickCount64() - dieTimeStart > MARIO_TIME_DIE)
    {
        if (mario.life > 0)
        {
            mario.life--;
        }

        CGame::GetInstance()->SwitchScene(WORLD_MAP_SCENE);
    }
    //DebugOut(L"MarioDieState %f %f\n", mario.vx, mario.vy);
}