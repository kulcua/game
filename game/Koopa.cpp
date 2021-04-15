#include "Koopa.h"
#include "Brick.h"
#include "Ground.h"
#include "BigBox.h"
#include "Pipe.h"
#include "Goomba.h"
#include "Mario.h"
#include "KoopaBound.h"

CKoopa::CKoopa()
{
	SetState(KOOPA_STATE_WALKING);
	level = KOOPA_LEVEL_WALK;
}

void CKoopa::HandleByMario(CMario* mario)
{
	isHandled = true;
	mario_ = mario;
}

void CKoopa::KickByMario(CMario* mario)
{
	isHandled = false;	 
	nx = mario->nx;
	vx = nx * KOOPA_BALL_SPEED;
}

void CKoopa::SetPositionHandled()
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

void CKoopa::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + KOOPA_BBOX_WIDTH;
	if (state == KOOPA_STATE_WALKING)
		b = y + KOOPA_BBOX_HEIGHT;
	else
		b = y + KOOPA_BBOX_HEIGHT_DIE;
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (isHandled)
		SetPositionHandled();
	else
	{
		vy += KOOPA_GRAVITY * dt;
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
		//if (ny != -1) // handle case obj fall down
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
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
				if (e->ny < 0)
				{
					isOnGround = true;
				}
				if (e->nx != 0)
				{
					if (state == KOOPA_STATE_BALL)
						vx = this->nx * KOOPA_BALL_SPEED;
					else
						vx = this->nx * KOOPA_WALKING_SPEED;
					x += dx;
				}
			}
			else if (dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				goomba->SetState(GOOMBA_STATE_DIE);
			}
			else if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny < 0)
					isOnGround = true;
				if (e->nx)
					vx = -vx;
			}
			else if (dynamic_cast<KoopaBound*>(e->obj))
			{
				if (e->nx != 0)
				{
					if (state != KOOPA_STATE_BALL)
					{
						this->nx = -this->nx;
						vx = this->nx * KOOPA_WALKING_SPEED;
					}
					else {
						vx = this->nx * KOOPA_BALL_SPEED;
						x += dx;
					}
				}
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopa::DowngradeLevel()
{
	level--;
	if (level == KOOPA_LEVEL_BALL)
		SetState(KOOPA_STATE_BALL);
	else if (level == KOOPA_LEVEL_WALK)
		SetState(KOOPA_STATE_WALKING);
}

void CKoopa::Render()
{
	int ani;
	if (state == KOOPA_STATE_BALL)
	{
		if (vx == 0)
			ani = KOOPA_ANI_BALL;
		else ani = KOOPA_ANI_BALL_ROLL;
	}
	else
		ani = KOOPA_ANI_WALKING;

	animation_set->at(ani)->Render(x, y, nx);
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_BALL:
		level = KOOPA_LEVEL_BALL;
		y += KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE;
		vx = 0;
		break;
	case KOOPA_STATE_WALKING:
		vx = nx * KOOPA_WALKING_SPEED;
		break;
	}
}