#include "Camera.h"
#include "Game.h"
#include "CameraBound.h"
#include "MarioFlyingState.h"

CCamera::CCamera(CMario* mario, float x, float y, float width, float height)
{
	this->mario = mario;
	game = CGame::GetInstance();
	this->width = width;
	this->height = height;
	x = mario->x - width / 2;
	if (x < 0) x = 0;
	SetPosition(x, y);
}

void CCamera::FollowMario()
{
	if ((mario->vx > 0 && mario->x > xCenter) // walk right
		|| (mario->vx < 0 && mario->x < xCenter)) // walk left
	{
		vx = mario->vx;		
	}
	else vx = 0;
		
	bool marioOnTopCam;
	if (mario->y < yCenter) // mario on top camera
		marioOnTopCam = true;	
	else
		marioOnTopCam = false;

	if (mario->isGrounded == false)
	{
		if ((marioOnTopCam == true && mario->vy < 0) // when mario fly
			|| (marioOnTopCam == false && mario->vy > 0)) // when mario drop
		{
			vy = mario->vy;
		}
	}
	else vy = 0;
}

void CCamera::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	xCenter = x + (width / 2);
	yCenter = y + (height / 2) - MARIO_BIG_BBOX_WIDTH;

	FollowMario();

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (mario->state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CCameraBound*>(e->obj))
			{
				CCameraBound* camBound = dynamic_cast<CCameraBound*>(e->obj);
				if (e->ny > 0)
				{
					if (camBound->GetType() == 1)
					{
						if (dynamic_cast<MarioFlyingState*>(mario->state_))
						{
							y += dy;
						}
					}
				}
			}
			else
			{
				if (e->ny) y += dy;
				else if (e->nx) x += dx;
			}
		}
	}		
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	game->SetCamPos(x, y);
}

void CCamera::Render()
{
	//RenderBoundingBox();
}

void CCamera::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}