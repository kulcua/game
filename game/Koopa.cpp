#include "Koopa.h"
#include "Brick.h"
#include "Ground.h"
#include "BigBox.h"
#include "Goomba.h"
#include "Mario.h"
#include "Game.h"
#include "KoopaBound.h"
#include "BrickBlock.h"
#include "EffectPool.h"
#include "MusicalNote.h"
#include "Item.h"
#include "Camera.h"

CKoopa::CKoopa()
{
	SetState(KOOPA_STATE_WALKING);
	level = KOOPA_LEVEL_WALK;
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
}

void CKoopa::HandleByMario()
{
	isHandled = true;
}

void CKoopa::KickByMario()
{
	isHandled = false;	 
	nx = mario->nx;
	vx = nx * KOOPA_BALL_SPEED;
}

void CKoopa::SetPositionHandled()
{
	if (mario->GetLevel() == MARIO_LEVEL_SMALL)
	{
		if (mario->nx < 0)
			SetPosition(mario->x - MARIO_SMALL_BIG_RACCOON_HANDLE_SHELL_WIDTH_LEFT, mario->y - MARIO_SMALL_HANDLED_SHELL_HEIGHT);
		else
			SetPosition(mario->x + MARIO_SMALL_BIG_HANDLE_SHELL_WIDTH_RIGHT, mario->y - MARIO_SMALL_HANDLED_SHELL_HEIGHT);
	}
	else if (mario->GetLevel() == MARIO_LEVEL_BIG || mario->GetLevel() == MARIO_LEVEL_FIRE)
	{
		if (mario->nx < 0)
			SetPosition(mario->x - MARIO_SMALL_BIG_RACCOON_HANDLE_SHELL_WIDTH_LEFT, mario->y + MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT);
		else
			SetPosition(mario->x + MARIO_SMALL_BIG_HANDLE_SHELL_WIDTH_RIGHT, mario->y + MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT);
	}
	else if (mario->GetLevel() == MARIO_LEVEL_RACCOON)
	{
		if (mario->nx < 0)
			SetPosition(mario->x - MARIO_SMALL_BIG_RACCOON_HANDLE_SHELL_WIDTH_LEFT, mario->y + MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT);
		else
			SetPosition(mario->x + MARIO_RACCOON_HANDLE_SHELL_WIDTH_RIGHT, mario->y + MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT);
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

void CKoopa::HandleCollision(vector<LPGAMEOBJECT>* coObjects)
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
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		/*if (state != KOOPA_STATE_WALKING)
			if (nx != 0) vx = 0;*/
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->nx != 0 && state == KOOPA_STATE_BALL)
				{
					if (brick->GetState() != BRICK_STATE_DISABLE)
						brick->SetState(BRICK_STATE_DISABLE);
					KoopaBallDeflectVx();
				}
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
			else if (dynamic_cast<CCamera*>(e->obj))
			{
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
				goomba->ny = -goomba->ny;
			}
			else if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny < 0)
					isOnGround = true;
				//if (state == KOOPA_STATE_BALL)
				//{
				//	if (e->nx != 0)
				//		KoopaBallDeflectVx();
				//}
			}
			else if (dynamic_cast<BrickBlock*>(e->obj))
			{
				BrickBlock* block = dynamic_cast<BrickBlock*>(e->obj);
				if (block->isCoin)
				{
					if (e->nx != 0) {
						if (state == KOOPA_STATE_WALKING)
							vx = this->nx * KOOPA_WALKING_SPEED;
						else if (state == KOOPA_STATE_BALL)
							vx = this->nx * KOOPA_BALL_SPEED;
					}
					//if (e->ny != 0) y += dy;
				}
				else {
					if (e->nx != 0 && state == KOOPA_STATE_BALL)
					{
						EffectPool::GetInstance()->CreateDebris(block->x, block->y);
						block->die = true;
						KoopaBallDeflectVx();
					}
				}
			}
			else if (dynamic_cast<MusicalNote*>(e->obj))
			{
				MusicalNote* note = dynamic_cast<MusicalNote*>(e->obj);
				if (e->nx != 0 && state == KOOPA_STATE_BALL)
				{
					if (note->GetType() == MUSICAL_NOTE_TYPE_WHITE)
					{
						note->Deflect(1);
						KoopaBallDeflectVx();
					}
					else vx = this->nx * KOOPA_BALL_SPEED;
				}
			}
			else if (dynamic_cast<KoopaBound*>(e->obj))
			{
				if (e->nx != 0)
				{
					if (state == KOOPA_STATE_BALL) {
						vx = this->nx * KOOPA_BALL_SPEED;
						x += dx;
					}	
					else {
						this->nx = -this->nx;
						vx = this->nx * KOOPA_WALKING_SPEED;
					}
				}
			}
			else if (dynamic_cast<CItem*>(e->obj))
			{
				if (state == KOOPA_STATE_BALL)
					vx = this->nx * KOOPA_BALL_SPEED;
				else
					vx = this->nx * KOOPA_WALKING_SPEED;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopa::KoopaBallDeflectVx()
{
	this->nx = -this->nx;
	vx = this->nx * KOOPA_BALL_SPEED;
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (isHandled)
		SetPositionHandled();
	else
	{
		vy += KOOPA_GRAVITY * dt;
	}

	HandleCollision(coObjects);

	//grid_->Move(this, x, y);
}

void CKoopa::DowngradeLevel()
{
	level--;
	if (level == KOOPA_LEVEL_BALL)
		SetState(KOOPA_STATE_BALL);
	else if (level == KOOPA_LEVEL_WALK)
	{
		Effect* effect = EffectPool::GetInstance()->Create();
		if (effect != NULL)
			effect->InitPoint(EffectPoint::p100, x, y);
		SetState(KOOPA_STATE_WALKING);
	}	
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

	animation_set->at(ani)->Render(x, y, nx, ny);

	//RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case KOOPA_STATE_BALL:
		{
			Effect* effect = EffectPool::GetInstance()->Create();
			if (effect != NULL)
				effect->InitPoint(EffectPoint::p200, x, y);
			level = KOOPA_LEVEL_BALL;
			y += KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE;
			vx = 0;
		}
		break;
		case KOOPA_STATE_WALKING:
		{
			vx = nx * KOOPA_WALKING_SPEED;
		}
		break;
	}
}
