#include "MarioOverWorldState.h"
#include "Mario.h"
#include "Game.h"

#define MARIO_OVERWORLD_SPEED 0.3f

MarioOverWorldState* MarioOverWorldState::__instance = NULL;

MarioOverWorldState* MarioOverWorldState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioOverWorldState();
    }
    return __instance;
}

void MarioOverWorldState::HandleInput(CMario& mario, Input input)
{
    if (input == Input::PRESS_LEFT)
    {
        mario.vx = -MARIO_OVERWORLD_SPEED;
    }
    else if (input == Input::PRESS_RIGHT)
    {
        mario.vx = MARIO_OVERWORLD_SPEED;
    }
    else if (input == Input::PRESS_DOWN)
    {
        mario.vy = MARIO_OVERWORLD_SPEED;
    }
    else if (input == Input::PRESS_UP)
    {
        mario.vy = -MARIO_OVERWORLD_SPEED;
    }
    else if (input == Input::PRESS_S)
    {
        if (sceneId != 0 && mario.vx == 0 && mario.vy == 0)
        {
            isSwitchScene = true;
        }
    }
}

void MarioOverWorldState::Enter(CMario& mario)
{
    if (mario.GetLevel() == MARIO_LEVEL_SMALL)
        mario.SetAnimation(MARIO_ANI_SMALL_OVERWORLD);
    else if (mario.GetLevel() == MARIO_LEVEL_BIG)
        mario.SetAnimation(MARIO_ANI_BIG_OVERWORLD);
    else
        mario.SetAnimation(MARIO_ANI_RACCOON_OVERWORLD);
}

void MarioOverWorldState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
    right = left + MARIO_WIDTH;
    bottom = top + MARIO_HEIGHT;
}

void MarioOverWorldState::Update(CMario& mario, DWORD dt)
{
    if (isSwitchScene)
    {
        isSwitchScene = false;
        CGame::GetInstance()->SwitchScene(sceneId);
    }
    //DebugOut(L"MarioOverWorldState %f %f\n", mario.vx, mario.vy);
}