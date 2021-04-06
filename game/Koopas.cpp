#include "Koopas.h"
#include "Brick.h"
#include "Ground.h"
#include "BigBox.h"
#include "Utils.h"
#include "Pipe.h"
#include "Goomba.h"
#include "Mario.h"

CKoopas::CKoopas(float start_x, float end_x)
{
	this->start_x = start_x;
	this->end_x = end_x;
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::HandleByMario(CMario* mario)
{
	isHandled = true;
	mario_ = mario;
}

void CKoopas::KickByMario(CMario* mario)
{
	isHandled = false;	 
	vx = mario->nx * KOOPAS_BALL_SPEED;
}

void CKoopas::SetPositionHandled()
{
	if (mario_->GetLevel() == MARIO_LEVEL_SMALL)
	{
		if (mario_->nx < 0)
			SetPosition(mario_->x - MARIO_SMALL_BIG_RACCOON_HANDLE_SHELL_WIDTH_LEFT, mario_->y - MARIO_SMALL_HANDLED_SHELL_HEIGHT);
		else
			SetPosition(mario_->x + MARIO_SMALL_BIG_HANDLE_SHELL_WIDTH_RIGHT, mario_->y - MARIO_SMALL_HANDLED_SHELL_HEIGHT);
	}
	else if (mario_->GetLevel() == MARIO_LEVEL_BIG || mario_->GetLevel() == MARIO_LEVEL_FIRE)
	{
		if (mario_->nx < 0)
			SetPosition(mario_->x - MARIO_SMALL_BIG_RACCOON_HANDLE_SHELL_WIDTH_LEFT, mario_->y + MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT);
		else
			SetPosition(mario_->x + MARIO_SMALL_BIG_HANDLE_SHELL_WIDTH_RIGHT, mario_->y + MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT);
	}
	else if (mario_->GetLevel() == MARIO_LEVEL_RACCOON)
	{
		if (mario_->nx < 0)
			SetPosition(mario_->x - MARIO_SMALL_BIG_RACCOON_HANDLE_SHELL_WIDTH_LEFT, mario_->y + MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT);
		else
			SetPosition(mario_->x + MARIO_RACCOON_HANDLE_SHELL_WIDTH_RIGHT, mario_->y + MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT);
	}
}

void CKoopas::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + KOOPAS_BBOX_WIDTH;
	if (state == KOOPAS_STATE_WALKING)
	{
		b = y + KOOPAS_BBOX_HEIGHT;
	}
	else
	{
		b = y + KOOPAS_BBOX_HEIGHT_DIE;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!die)
	{
		CGameObject::Update(dt, coObjects);

		if (isHandled)
		{
			SetPositionHandled();
		}
		else
		{
			vy += KOOPAS_GRAVITY * dt;
		}

		if (state != KOOPAS_STATE_BALL)
		{
			if (vx < 0 && x < start_x)
			{
				x = start_x;
				vx = -vx;
				nx = 1;
			}

			if (vx > 0 && x > end_x - KOOPAS_BBOX_WIDTH) {
				x = end_x - KOOPAS_BBOX_WIDTH;
				vx = -vx;
				nx = -1;
			}
		}
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
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.4f;
			if (ny != -1) // handle case obj fall down
				y += min_ty * dy + ny * 0.4f;
				
			if (ny != 0) vy = 0;

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj))
				{
					CBrick* brick = dynamic_cast<CBrick*>(e->obj);
					brick->SetState(BRICK_STATE_DISABLE);
				}
				else if (dynamic_cast<CBigBox*>(e->obj))
				{
					x += dx;
				}
				else if (dynamic_cast<CGoomba*>(e->obj))
				{
					CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
					goomba->SetState(GOOMBA_STATE_DIE);
				}
				else if (e->nx)
					vx = -vx;
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CKoopas::Render()
{
	if (die == false)
	{
		int ani;
		if (state == KOOPAS_STATE_DIE)
		{
			ani = KOOPAS_ANI_DIE;
		}
		else if (state == KOOPAS_STATE_BALL)
			ani = KOOPAS_ANI_BALL;
		else
			ani = KOOPAS_ANI_WALKING;
		animation_set->at(ani)->Render(x, y, nx);
	}
	
	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE;
		break;
	case KOOPAS_STATE_BALL:
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE;
		vx = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = KOOPAS_WALKING_SPEED;
		break;
	}
}
