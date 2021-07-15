#include "Goomba.h"
#include "Ground.h"
#include "EffectPool.h"
#include "BigBox.h"
#include "CameraBound.h"
#include "Brick.h"
#include "BrickBlock.h"

CGoomba::CGoomba()
{
	SetState(GOOMBA_STATE_WALKING);
	die = false;
	level = GOOMBA_LEVEL_NO_WING;
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::HandleCollision(vector<LPGAMEOBJECT>* coObjects)
{
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

			if (dynamic_cast<Enermy*>(e->obj))
			{
				if (e->nx) {
					vx = this->nx * GOOMBA_WALKING_SPEED;
					x += dx;
				}
			}

			if (dynamic_cast<CGround*>(e->obj)
				|| dynamic_cast<BrickBlock*>(e->obj)
				|| dynamic_cast<CBrick*>(e->obj))
			{
				if (e->ny < 0) isOnGround = true;
				if (e->nx) {
					this->nx = -this->nx;
					vx = this->nx * GOOMBA_WALKING_SPEED;
				}
			}
			else if (dynamic_cast<CBigBox*>(e->obj))
			{
				if (e->nx)
				{
					vx = this->nx * GOOMBA_WALKING_SPEED;
					x += dx;
				}
			}
			else if (dynamic_cast<CCameraBound*>(e->obj))
			{
				x += dx;
				y += dy;
				die = true;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (GetTickCount64() - dieTimeStart > ENERMY_DIE_TIME && dieTimeStart > 0)
	{
		die = true;
	}

	vy += GOOMBA_GRAVITY * dt;
	
	HandleCollision(coObjects);

	grid_->Move(this, x, y);
}

void CGoomba::Render()
{
	int ani;
	if (dieTimeStart == 0)
	{
		ani = GOOMBA_ANI_WALKING;
	}
	else {
		ani = GOOMBA_ANI_DIE;
	}
	animation_set->at(ani)->Render(x, y, nx, ny);
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
	{
		Effect* effect = EffectPool::GetInstance()->Create();
		if (effect != NULL)
			effect->InitPoint(EffectPoint::p100, x, y);

		StartDieTime();
		vx = 0;
		break;
	}
	case GOOMBA_STATE_WALKING:
		vx = nx * GOOMBA_WALKING_SPEED;
		break;
	}
}

void CGoomba::DowngradeLevel()
{
	level--;
	if (level == 0)
		SetState(GOOMBA_STATE_DIE);
	else {
		Effect* effect = EffectPool::GetInstance()->Create();
		if (effect != NULL)
			effect->InitPoint(EffectPoint::p100, x, y);
	}
}
