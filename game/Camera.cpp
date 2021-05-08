#include "Camera.h"
#include "Game.h"
#include "CameraBound.h"
#include "MarioFlyingState.h"
#include "HUD.h"

#define CAM_WIDTH 800
#define CAM_HEIGHT 600

CCamera::CCamera(float x, float y)
{
	mario = CMario::GetInstance();
	game = CGame::GetInstance();
	this->width = CAM_WIDTH;
	this->height = CAM_HEIGHT;
	x = mario->x - width / 2;
	if (x < 0) x = 0;
	SetPosition(x, y);
}

void CCamera::FollowMario()
{
	xCenter = x + (width / 2) - MARIO_BIG_BBOX_WIDTH / 2;
	yCenter = y + (height / 2) + MARIO_BIG_BBOX_HEIGHT / 2;

	if ((mario->vx > 0 && mario->x < xCenter) // walk right
		|| (mario->vx < 0 && mario->x > xCenter))// walk left
	{
		vx = 0.0f;
	}
	else vx = mario->vx;
	
	bool marioOnTopCam;
	if (mario->y < yCenter) // mario on top camera
		marioOnTopCam = true;	
	else
		marioOnTopCam = false;

	if (dynamic_cast<MarioFlyingState*>(mario->state_) && mario->GetLevel() == MARIO_LEVEL_RACCOON)
		onGroundMode = false;

	if (onGroundMode == false)
	{
		if ((marioOnTopCam == true && mario->vy < 0) // when mario fly
			|| (marioOnTopCam == false && mario->vy > 0)) // drop
		{
			vy = mario->vy;
		}
		else vy = 0.0f;
	}
}

void CCamera::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

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

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CCameraBound*>(e->obj))
			{
				CCameraBound* camBound = dynamic_cast<CCameraBound*>(e->obj);
				
				if (camBound->GetType() == 0)
				{
					if (e->ny < 0)
						onGroundMode = true;
				}		
			}
			else {
				if (nx != 0)
				{
					vx = mario->vx;
					x += dx;
				}
				if (ny != 0) {
					y += dy;
				}
			}
		}
	}		
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	game->SetCamPos(x, y);
	HUD::GetInstance()->SetPosition(x, y + SCREEN_HEIGHT - HUD_HEIGHT);
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