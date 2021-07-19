#include "Camera.h"
#include "Game.h"
#include "CameraBound.h"
#include "MarioFlyingState.h"
#include "HUD.h"
#include "MarioFrontState.h"

CCamera::CCamera()
{
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();;
	this->width = CAM_WIDTH;
	this->height = CAM_HEIGHT;
}

void CCamera::SetPosition(float y) {
	x = mario->x - width / 2;
	if (x < CAM_INIT_BOUND) x = CAM_INIT_BOUND;
	this->y = y;
	startX = x;
	startY = y;
}

void CCamera::FollowMario()
{
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
		isOnGroundMode = false;

	if (isOnGroundMode == false)
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
	if (isMove == true)
	{
		CGameObject::Update(dt);

		xCenter = x + (width / 2) - MARIO_BIG_BBOX_WIDTH / 2;
		yCenter = y + (height / 2) + MARIO_BIG_BBOX_HEIGHT / 2;

		FollowMario();

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, nx, ny);

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CCameraBound*>(e->obj))
				{
					CCameraBound* camBound = dynamic_cast<CCameraBound*>(e->obj);

					if (camBound->GetType() == 0)
					{
						if (e->ny < 0)
							isOnGroundMode = true;
					}
				}
				else {
					if (nx != 0)
					{
						x += dx;
					}
					if (ny != 0) {
						y += dy;
					}
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
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