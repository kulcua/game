#include "MusicalNote.h"
#include "Utils.h"
#include "Game.h"
#include "Mario.h"
#include "MarioJumpingState.h"
#include "PortalManager.h"
#include "PortalPipe.h"

MusicalNote::MusicalNote(int type, float startY)
{
	switchPortTimeStart = 0;
	SetAnimation(MUSICAL_NOTE_ANI_ID);
	this->type = type;
	if (type == 1)
		isHidden = false;
	else isHidden = true;
	this->startY = startY;
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
}

void MusicalNote::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	y += dy;
	
	if ((y < startY && nDeflect > 0) || (y > startY && nDeflect < 0)) // take to start_y after deflect cause disable
	{
		vy += nDeflect * MUSICAL_NOTE_VY_RETURN;
		if (mario->input == Input::PRESS_S)
		{
			if (GetType() == MUSICAL_NOTE_TYPE_RED)
			{
				mario->vy = nDeflect * MUSICAL_NOTE_DEFLECT_MARIO_RED;
				StartSwitchPort();
			}
			else {
				mario->vy = nDeflect * MUSICAL_NOTE_DEFLECT_MARIO_WHITE;
			}
		}
	}
	else if (nDeflect != 0)
	{
		mario->isOnGround = false;
		if (mario->input != Input::PRESS_S)
		{
			mario->vy = nDeflect * MUSICAL_NOTE_DEFLECT_MARIO_DEFAULT;
		}
		mario->vx = 0;
		mario->state_ = MarioState::jumping.GetInstance();
		y = startY;
		vy = 0;
		nDeflect = 0;
	}

	if (switchPortTimeStart > 0 && GetTickCount64() - switchPortTimeStart > MUSICAL_NOTE_SWITCH_PORT_TIME)
	{
		switchPortTimeStart = 0;
		PortalPipe *portOut = PortalPipeOutManager::GetInstance()->GetPortalPipeOut(portIn);
		mario->SetPosition(portOut->x, portOut->y);
		mario->vy = -MARIO_JUMP_SPEED_Y;
		CGame::GetInstance()->GetCam()->SetPosition(portOut->GetCamY());
		CGame::GetInstance()->GetCam()->x = portOut->x;
		CGame::GetInstance()->GetCam()->isScroll = true;
	}
}

void MusicalNote::Deflect(float ny)
{
	if (nDeflect == 0)
	{
		nDeflect = ny;
		this->vy = -nDeflect * MUSICAL_NOTE_VY_DEFLECT;
	}
}

void MusicalNote::Render()
{
	if (isHidden == false)
	{
		int ani = 0;
		if (type == MUSICAL_NOTE_TYPE_WHITE || nDeflect != 0)
			ani = MUSICAL_NOTE_ANI_WHITE;
		else ani = MUSICAL_NOTE_ANI_RED;
		animation_set->at(ani)->Render(x, y, nx, ny);
	}	
}

void MusicalNote::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MUSICAL_NOTE_BBOX_SIZE;
	b = y + MUSICAL_NOTE_BBOX_SIZE;
}