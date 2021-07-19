#include "MarioFrontState.h"
#include "Mario.h"
#include "MarioStandingState.h"
#include "MarioJumpingState.h"
#include "MarioDroppingState.h"
#include "Game.h"

MarioFrontState* MarioFrontState::__instance = NULL;

MarioFrontState* MarioFrontState::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MarioFrontState();
    }
    return __instance;
}

void MarioFrontState::HandleInput(CMario& mario, Input input)
{

}

void MarioFrontState::Enter(CMario& mario)
{
    if (mario.GetLevel() == MARIO_LEVEL_SMALL)
    {
        mario.SetAnimation(MARIO_ANI_FRONT_SMALL);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_BIG)
    {
        mario.SetAnimation(MARIO_ANI_FRONT_BIG);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_RACCOON)
    {
        mario.SetAnimation(MARIO_ANI_FRONT_RACCOON);
    }
    else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
    {
        mario.SetAnimation(MARIO_ANI_FRONT_FIRE);
    }
}

void MarioFrontState::GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom)
{
    MarioState::GetBoundingBox(mario, left, top, right, bottom);
}

void MarioFrontState::Update(CMario& mario, DWORD dt)
{
    onPortalPipe = false;

    mario.vx = 0;
    if (eny < 0) mario.vy = MARIO_FRONT_SPEED_DOWN;
    else mario.vy = MARIO_FRONT_SPEED_UP;
 
    mario.y += mario.dy;

    if (getOut)
    {
        if (mario.GetLevel() == MARIO_LEVEL_SMALL)
        {
            if ((mario.y > portOut->y + MARIO_SMALL_BBOX_HEIGHT) || (mario.y < portOut->y - MARIO_SMALL_BBOX_HEIGHT))
            {
                if (eny > 0) mario.state_ = MarioState::standing.GetInstance();
                else
                {
                    mario.isOnGround = false;
                    mario.state_ = MarioState::dropping.GetInstance();
                }
                getOut = false;
            }
        }
        else if ((mario.y > portOut->y + MARIO_RACCOON_BBOX_HEIGHT) || (mario.y < portOut->y - MARIO_RACCOON_BBOX_HEIGHT))
        {
            if (eny > 0) mario.state_ = MarioState::standing.GetInstance();
            else
            {
                mario.isOnGround = false;
                mario.state_ = MarioState::dropping.GetInstance();
            }
            getOut = false;
        }
        CGame::GetInstance()->GetCam()->isOnGround = false;
    }
    else if ((mario.y > portIn->y && mario.vy > 0) || (mario.y < portIn->y && mario.vy < 0))
    {
        mario.SetPosition(portOut->x, portOut->y);
        CGame::GetInstance()->GetCam()->SetPosition(portOut->GetCamY());
        getOut = true;
    }
    //DebugOut(L"MarioFrontState %f %f %d\n", mario.vy, mario.y, getOut);
}

void MarioFrontState::GetPortal(CMario& mario, PortalPipe* port, float eny)
{
    onPortalPipe = true;
    portIn = port;
    portOut = PortalPipeOutManager::GetInstance()->GetPortalPipeOut(port->GetType());
    this->eny = eny;
}